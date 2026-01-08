<?php
$DB_HOST = 'localhost';
$DB_NAME = 'wegabox';
$DB_USER = 'wegabox';
$DB_PASS = 'Tem2006!@';
try {
    $pdo = new PDO("mysql:host=$DB_HOST;dbname=$DB_NAME;charset=utf8mb4", $DB_USER, $DB_PASS);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) { die("Ошибка БД"); }

// AJAX обработчик переключения насосов
if (isset($_GET['action']) && $_GET['action'] === 'toggle_pump') {
    header('Content-Type: application/json');
    $pump = intval($_GET['pump'] ?? 0);
    $state = intval($_GET['state'] ?? 0);
    if ($pump >= 1 && $pump <= 4) {
        $pdo->prepare("UPDATE pumps SET pump$pump = ? WHERE id = 1")->execute([$state]);
        echo json_encode(['ok' => true, 'pump' => $pump, 'state' => $state]);
    } else {
        echo json_encode(['ok' => false, 'error' => 'Invalid pump']);
    }
    exit;
}

$stmt = $pdo->query("SELECT * FROM readings ORDER BY created_at DESC LIMIT 1");
$last = $stmt->fetch(PDO::FETCH_ASSOC) ?: [];
$stmt = $pdo->query("SELECT * FROM calibration ORDER BY id DESC LIMIT 1");
$calib = $stmt->fetch(PDO::FETCH_ASSOC) ?: [];
$stmt = $pdo->query("SELECT * FROM pumps ORDER BY id DESC LIMIT 1");
$pumps = $stmt->fetch(PDO::FETCH_ASSOC) ?: [];
$page = $_GET['page'] ?? 'dashboard';

$period = $_GET['period'] ?? 'day';
$periodHours = ['hour' => 1, 'day' => 24, 'week' => 168, 'month' => 720];
$hours = $periodHours[$period] ?? 24;
$periodNames = ['hour' => 'Час', 'day' => 'День', 'week' => 'Неделя', 'month' => 'Месяц'];

$chartData = [];
if ($page === 'dashboard' || $page === 'charts') {
    $stmt = $pdo->prepare("SELECT root_temp, air_temp, air_hum, ph, ec, distance, created_at 
                           FROM readings 
                           WHERE created_at >= DATE_SUB(NOW(), INTERVAL ? HOUR)
                           AND (root_temp IS NOT NULL OR air_temp IS NOT NULL OR ph IS NOT NULL OR ec IS NOT NULL)
                           ORDER BY created_at ASC");
    $stmt->execute([$hours]);
    $chartData = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
    $stmt = $pdo->prepare("SELECT 
        MIN(root_temp) as min_root, MAX(root_temp) as max_root, AVG(root_temp) as avg_root,
        MIN(air_temp) as min_air, MAX(air_temp) as max_air, AVG(air_temp) as avg_air,
        MIN(air_hum) as min_hum, MAX(air_hum) as max_hum, AVG(air_hum) as avg_hum,
        MIN(ph) as min_ph, MAX(ph) as max_ph, AVG(ph) as avg_ph,
        MIN(ec) as min_ec, MAX(ec) as max_ec, AVG(ec) as avg_ec,
        MIN(distance) as min_dist, MAX(distance) as max_dist, AVG(distance) as avg_dist
        FROM readings WHERE created_at >= DATE_SUB(NOW(), INTERVAL ? HOUR)");
    $stmt->execute([$hours]);
    $stats = $stmt->fetch(PDO::FETCH_ASSOC) ?: [];
}
?>
<!DOCTYPE html>
<html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>WegaBox - Гидропоника</title>
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<style>*{margin:0;padding:0;box-sizing:border-box}body{font-family:-apple-system,sans-serif;background:#0d1117;color:#c9d1d9;min-height:100vh}.container{max-width:1400px;margin:0 auto;padding:20px}header{background:#161b22;border-bottom:1px solid #30363d;padding:15px 0;margin-bottom:30px}header .container{display:flex;justify-content:space-between;align-items:center;flex-wrap:wrap;gap:10px}.logo{font-size:24px;font-weight:bold;color:#58a6ff}.logo span{color:#8b949e;font-weight:normal;font-size:14px}nav{display:flex;gap:5px;flex-wrap:wrap}nav a{color:#8b949e;text-decoration:none;padding:8px 16px;border-radius:6px}nav a:hover{background:#21262d;color:#c9d1d9}nav a.active{background:#238636;color:#fff}.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(180px,1fr));gap:15px;margin-bottom:30px}.card{background:#161b22;border:1px solid #30363d;border-radius:8px;padding:20px}.card-title{color:#8b949e;font-size:12px;text-transform:uppercase;margin-bottom:8px}.card-value{font-size:28px;font-weight:bold;color:#58a6ff}.card-unit{color:#8b949e;font-size:14px}.card-stats{margin-top:10px;font-size:11px;color:#8b949e}.section{background:#161b22;border:1px solid #30363d;border-radius:8px;padding:20px;margin-bottom:20px}.section-title{font-size:18px;margin-bottom:20px;display:flex;justify-content:space-between;align-items:center}table{width:100%;border-collapse:collapse}th,td{padding:12px;text-align:left;border-bottom:1px solid #30363d}th{color:#8b949e}.form-group{margin-bottom:15px}label{display:block;color:#8b949e;margin-bottom:5px}input,select{width:100%;padding:10px;background:#0d1117;border:1px solid #30363d;border-radius:6px;color:#c9d1d9}input:focus{border-color:#58a6ff;outline:none}.btn{padding:10px 20px;border:none;border-radius:6px;cursor:pointer}.btn-primary{background:#238636;color:#fff}.pump-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(150px,1fr));gap:15px}.pump-card{background:#0d1117;border:2px solid #30363d;border-radius:8px;padding:20px;text-align:center;cursor:pointer}.pump-card.active{border-color:#3fb950;background:rgba(63,185,80,0.1)}.pump-icon{font-size:40px;margin-bottom:10px}.pump-status{color:#8b949e;font-size:12px;margin-top:5px}.pump-card.active .pump-status{color:#3fb950}.status{display:inline-block;width:10px;height:10px;border-radius:50%;margin-right:8px}.status.online{background:#3fb950;box-shadow:0 0 10px #3fb950}.status.offline{background:#f85149}.alert{padding:15px;border-radius:6px;margin-bottom:20px}.alert-info{background:rgba(88,166,255,0.1);border:1px solid #58a6ff;color:#58a6ff}.alert-success{background:rgba(63,185,80,0.1);border:1px solid #3fb950;color:#3fb950}.two-col{display:grid;grid-template-columns:1fr 1fr;gap:20px}.chart-container{position:relative;height:300px;margin-bottom:20px}.period-selector{display:flex;gap:5px}.period-selector a{padding:6px 14px;border-radius:4px;color:#8b949e;text-decoration:none;font-size:13px;border:1px solid #30363d}.period-selector a:hover{background:#21262d;color:#c9d1d9}.period-selector a.active{background:#238636;color:#fff;border-color:#238636}.stat-box{display:inline-block;background:#0d1117;padding:4px 8px;border-radius:4px;margin:2px;font-size:11px}.stat-box.min{color:#58a6ff}.stat-box.max{color:#f85149}.stat-box.avg{color:#3fb950}@media(max-width:768px){.two-col{grid-template-columns:1fr}nav{flex-wrap:wrap}.chart-container{height:250px}.grid{grid-template-columns:repeat(auto-fit,minmax(150px,1fr))}}</style>
</head><body>
<header><div class="container"><div class="logo">🌱 WegaBox <span>v2.3</span></div>
<nav><a href="?page=dashboard" class="<?=$page==='dashboard'?'active':''?>">Главная</a>
<a href="?page=charts&period=<?=$period?>" class="<?=$page==='charts'?'active':''?>">Графики</a>
<a href="?page=sensors" class="<?=$page==='sensors'?'active':''?>">Датчики</a>
<a href="?page=calibration" class="<?=$page==='calibration'?'active':''?>">Калибровка</a>
<a href="?page=pumps" class="<?=$page==='pumps'?'active':''?>">Насосы</a>
<a href="?page=history" class="<?=$page==='history'?'active':''?>">История</a>
<a href="?page=logs" class="<?=$page==='logs'?'active':''?>">Логи</a></nav></div></header>
<div class="container">

<?php if($page==='dashboard'): $isOnline=(time()-strtotime($last['created_at']??'2000-01-01'))<120; ?>
<div style="display:flex;align-items:center;margin-bottom:20px;justify-content:space-between;flex-wrap:wrap;gap:10px">
<div><span class="status <?=$isOnline?'online':'offline'?>"></span><span>Обновлено: <?=$last['created_at']??'Нет данных'?></span></div>
<div class="period-selector">
    <a href="?page=dashboard&period=hour" class="<?=$period==='hour'?'active':''?>">Час</a>
    <a href="?page=dashboard&period=day" class="<?=$period==='day'?'active':''?>">День</a>
    <a href="?page=dashboard&period=week" class="<?=$period==='week'?'active':''?>">Неделя</a>
    <a href="?page=dashboard&period=month" class="<?=$period==='month'?'active':''?>">Месяц</a>
</div>
</div>
<?php if(empty($last)):?><div class="alert alert-info">⏳ Ожидание данных от ESP32...</div><?php endif;?>
<div class="grid">
<div class="card"><div class="card-title">🌡️ Т Корней</div><div class="card-value"><?=isset($last['root_temp'])?number_format($last['root_temp'],1):'--'?><span class="card-unit">°C</span></div>
<div class="card-stats"><span class="stat-box min">↓<?=isset($stats['min_root'])?number_format($stats['min_root'],1):'-'?></span><span class="stat-box avg">~<?=isset($stats['avg_root'])?number_format($stats['avg_root'],1):'-'?></span><span class="stat-box max">↑<?=isset($stats['max_root'])?number_format($stats['max_root'],1):'-'?></span></div></div>
<div class="card"><div class="card-title">🌡️ Т Воздуха</div><div class="card-value"><?=isset($last['air_temp'])?number_format($last['air_temp'],1):'--'?><span class="card-unit">°C</span></div>
<div class="card-stats"><span class="stat-box min">↓<?=isset($stats['min_air'])?number_format($stats['min_air'],1):'-'?></span><span class="stat-box avg">~<?=isset($stats['avg_air'])?number_format($stats['avg_air'],1):'-'?></span><span class="stat-box max">↑<?=isset($stats['max_air'])?number_format($stats['max_air'],1):'-'?></span></div></div>
<div class="card"><div class="card-title">💧 Влажность</div><div class="card-value"><?=isset($last['air_hum'])?number_format($last['air_hum'],1):'--'?><span class="card-unit">%</span></div>
<div class="card-stats"><span class="stat-box min">↓<?=isset($stats['min_hum'])?number_format($stats['min_hum'],1):'-'?></span><span class="stat-box avg">~<?=isset($stats['avg_hum'])?number_format($stats['avg_hum'],1):'-'?></span><span class="stat-box max">↑<?=isset($stats['max_hum'])?number_format($stats['max_hum'],1):'-'?></span></div></div>
<div class="card"><div class="card-title">⚗️ pH</div><div class="card-value"><?=isset($last['ph'])?number_format($last['ph'],2):'--'?></div>
<div class="card-stats"><span class="stat-box min">↓<?=isset($stats['min_ph'])?number_format($stats['min_ph'],2):'-'?></span><span class="stat-box avg">~<?=isset($stats['avg_ph'])?number_format($stats['avg_ph'],2):'-'?></span><span class="stat-box max">↑<?=isset($stats['max_ph'])?number_format($stats['max_ph'],2):'-'?></span></div></div>
<div class="card"><div class="card-title">⚡ EC</div><div class="card-value"><?=isset($last['ec'])?number_format($last['ec'],2):'--'?><span class="card-unit">мС</span></div>
<div class="card-stats"><span class="stat-box min">↓<?=isset($stats['min_ec'])?number_format($stats['min_ec'],2):'-'?></span><span class="stat-box avg">~<?=isset($stats['avg_ec'])?number_format($stats['avg_ec'],2):'-'?></span><span class="stat-box max">↑<?=isset($stats['max_ec'])?number_format($stats['max_ec'],2):'-'?></span></div></div>
<div class="card"><div class="card-title">📏 Уровень</div><div class="card-value"><?=isset($last['distance'])?number_format($last['distance'],1):'--'?><span class="card-unit">см</span></div>
<div class="card-stats"><span class="stat-box min">↓<?=isset($stats['min_dist'])?number_format($stats['min_dist'],1):'-'?></span><span class="stat-box avg">~<?=isset($stats['avg_dist'])?number_format($stats['avg_dist'],1):'-'?></span><span class="stat-box max">↑<?=isset($stats['max_dist'])?number_format($stats['max_dist'],1):'-'?></span></div></div>
<div class="card"><div class="card-title">☀️ Свет</div><div class="card-value"><?=$last['light']??'--'?></div></div>
<div class="card"><div class="card-title">📶 Сигнал</div><div class="card-value"><?=$last['rssi']??'--'?><span class="card-unit">дБм</span></div></div>
</div>

<div class="two-col">
<div class="section">
    <div class="section-title">🌡️ Температура</div>
    <div class="chart-container"><canvas id="tempChart"></canvas></div>
</div>
<div class="section">
    <div class="section-title">⚗️ pH и EC</div>
    <div class="chart-container"><canvas id="phEcChart"></canvas></div>
</div>
</div>

<div class="section"><div class="section-title">💧 Насосы</div><div class="pump-grid">
<?php for($i=1;$i<=4;$i++):?><div class="pump-card <?=($pumps["pump$i"]??0)?'active':''?>" id="pump<?=$i?>" onclick="togglePump(<?=$i?>)"><div class="pump-icon">💧</div><div><?=$pumps["pump{$i}_name"]??"Насос $i"?></div><div class="pump-status" id="pump<?=$i?>_status"><?=($pumps["pump$i"]??0)?'ВКЛ':'ВЫКЛ'?></div></div><?php endfor;?>
</div></div>
<script>
function togglePump(num) {
    const card = document.getElementById('pump' + num);
    const status = document.getElementById('pump' + num + '_status');
    const isActive = card.classList.contains('active');
    const newState = isActive ? 0 : 1;
    
    // Отправляем на сервер
    fetch('?action=toggle_pump&pump=' + num + '&state=' + newState)
        .then(r => r.json())
        .then(data => {
            if (data.ok) {
                card.classList.toggle('active');
                status.textContent = newState ? 'ВКЛ' : 'ВЫКЛ';
            }
        });
}
</script>

<?php elseif($page==='charts'):?>
<div style="margin-bottom:20px;display:flex;justify-content:space-between;align-items:center;flex-wrap:wrap;gap:10px">
<h2>📊 Аналитика</h2>
<div class="period-selector">
    <a href="?page=charts&period=hour" class="<?=$period==='hour'?'active':''?>">Час</a>
    <a href="?page=charts&period=day" class="<?=$period==='day'?'active':''?>">День</a>
    <a href="?page=charts&period=week" class="<?=$period==='week'?'active':''?>">Неделя</a>
    <a href="?page=charts&period=month" class="<?=$period==='month'?'active':''?>">Месяц</a>
</div>
</div>

<div class="section">
    <div class="section-title">
        <span>🌡️ Температура</span>
        <span style="font-size:12px;color:#8b949e">
            <span class="stat-box min">Мин: <?=isset($stats['min_root'])?number_format($stats['min_root'],1):'-'?>°C</span>
            <span class="stat-box avg">Сред: <?=isset($stats['avg_root'])?number_format($stats['avg_root'],1):'-'?>°C</span>
            <span class="stat-box max">Макс: <?=isset($stats['max_root'])?number_format($stats['max_root'],1):'-'?>°C</span>
        </span>
    </div>
    <div class="chart-container" style="height:350px"><canvas id="tempChartFull"></canvas></div>
</div>

<div class="section">
    <div class="section-title">
        <span>💧 Влажность</span>
        <span style="font-size:12px;color:#8b949e">
            <span class="stat-box min">Мин: <?=isset($stats['min_hum'])?number_format($stats['min_hum'],1):'-'?>%</span>
            <span class="stat-box avg">Сред: <?=isset($stats['avg_hum'])?number_format($stats['avg_hum'],1):'-'?>%</span>
            <span class="stat-box max">Макс: <?=isset($stats['max_hum'])?number_format($stats['max_hum'],1):'-'?>%</span>
        </span>
    </div>
    <div class="chart-container" style="height:350px"><canvas id="humChart"></canvas></div>
</div>

<div class="section">
    <div class="section-title">
        <span>⚗️ pH</span>
        <span style="font-size:12px;color:#8b949e">
            <span class="stat-box min">Мин: <?=isset($stats['min_ph'])?number_format($stats['min_ph'],2):'-'?></span>
            <span class="stat-box avg">Сред: <?=isset($stats['avg_ph'])?number_format($stats['avg_ph'],2):'-'?></span>
            <span class="stat-box max">Макс: <?=isset($stats['max_ph'])?number_format($stats['max_ph'],2):'-'?></span>
        </span>
    </div>
    <div class="chart-container" style="height:350px"><canvas id="phChart"></canvas></div>
</div>

<div class="section">
    <div class="section-title">
        <span>⚡ EC</span>
        <span style="font-size:12px;color:#8b949e">
            <span class="stat-box min">Мин: <?=isset($stats['min_ec'])?number_format($stats['min_ec'],2):'-'?> мС</span>
            <span class="stat-box avg">Сред: <?=isset($stats['avg_ec'])?number_format($stats['avg_ec'],2):'-'?> мС</span>
            <span class="stat-box max">Макс: <?=isset($stats['max_ec'])?number_format($stats['max_ec'],2):'-'?> мС</span>
        </span>
    </div>
    <div class="chart-container" style="height:350px"><canvas id="ecChart"></canvas></div>
</div>

<div class="section">
    <div class="section-title">
        <span>📏 Уровень</span>
        <span style="font-size:12px;color:#8b949e">
            <span class="stat-box min">Мин: <?=isset($stats['min_dist'])?number_format($stats['min_dist'],1):'-'?> см</span>
            <span class="stat-box avg">Сред: <?=isset($stats['avg_dist'])?number_format($stats['avg_dist'],1):'-'?> см</span>
            <span class="stat-box max">Макс: <?=isset($stats['max_dist'])?number_format($stats['max_dist'],1):'-'?> см</span>
        </span>
    </div>
    <div class="chart-container" style="height:350px"><canvas id="levelChart"></canvas></div>
</div>

<?php elseif($page==='sensors'):?>
<div class="section"><div class="section-title">📊 Все датчики</div>
<?php if(empty($last)):?><div class="alert alert-info">Нет данных</div><?php else:?>
<table><tr><th>Датчик</th><th>Значение</th><th>Ед.</th></tr>
<tr><td>Температура корней</td><td><?=$last['root_temp']??'-'?></td><td>°C</td></tr>
<tr><td>Температура воздуха</td><td><?=$last['air_temp']??'-'?></td><td>°C</td></tr>
<tr><td>Температура CPU</td><td><?=$last['cpu_temp']??'-'?></td><td>°C</td></tr>
<tr><td>Влажность воздуха</td><td><?=$last['air_hum']??'-'?></td><td>%</td></tr>
<tr><td>pH</td><td><?=$last['ph']??'-'?></td><td>pH</td></tr>
<tr><td>pH (мВ)</td><td><?=$last['ph_mv']??'-'?></td><td>мВ</td></tr>
<tr><td>EC</td><td><?=$last['ec']??'-'?></td><td>мС/см</td></tr>
<tr><td>Уровень раствора</td><td><?=$last['distance']??'-'?></td><td>см</td></tr>
<tr><td>Освещённость</td><td><?=$last['light']??'-'?></td><td></td></tr>
<tr><td>NTC</td><td><?=$last['ntc']??'-'?></td><td></td></tr>
<tr><td>WiFi сигнал</td><td><?=$last['rssi']??'-'?></td><td>дБм</td></tr>
</table><?php endif;?></div>

<?php elseif($page==='calibration'):
if($_SERVER['REQUEST_METHOD']==='POST'&&isset($_POST['save'])){
$c=$pdo->query("SELECT COUNT(*) FROM calibration")->fetchColumn();
if($c==0){$pdo->prepare("INSERT INTO calibration(device_id,ntc_b,ntc_r25,ec_r1,ec_kt,ec_val_p1,ec_val_p2,ec_r2_p1,ec_r2_p2,ec_val_korr,ph_val_p1,ph_val_p2,ph_val_p3,ph_raw_p1,ph_raw_p2,ph_raw_p3)VALUES('wegabox',?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)")->execute([$_POST['ntc_b'],$_POST['ntc_r25'],$_POST['ec_r1'],$_POST['ec_kt'],$_POST['ec_val_p1'],$_POST['ec_val_p2'],$_POST['ec_r2_p1'],$_POST['ec_r2_p2'],$_POST['ec_val_korr'],$_POST['ph_val_p1'],$_POST['ph_val_p2'],$_POST['ph_val_p3'],$_POST['ph_raw_p1'],$_POST['ph_raw_p2'],$_POST['ph_raw_p3']]);}
else{$pdo->prepare("UPDATE calibration SET ntc_b=?,ntc_r25=?,ec_r1=?,ec_kt=?,ec_val_p1=?,ec_val_p2=?,ec_r2_p1=?,ec_r2_p2=?,ec_val_korr=?,ph_val_p1=?,ph_val_p2=?,ph_val_p3=?,ph_raw_p1=?,ph_raw_p2=?,ph_raw_p3=? WHERE id=1")->execute([$_POST['ntc_b'],$_POST['ntc_r25'],$_POST['ec_r1'],$_POST['ec_kt'],$_POST['ec_val_p1'],$_POST['ec_val_p2'],$_POST['ec_r2_p1'],$_POST['ec_r2_p2'],$_POST['ec_val_korr'],$_POST['ph_val_p1'],$_POST['ph_val_p2'],$_POST['ph_val_p3'],$_POST['ph_raw_p1'],$_POST['ph_raw_p2'],$_POST['ph_raw_p3']]);}
echo'<div class="alert alert-success">✓ Сохранено!</div>';$calib=$pdo->query("SELECT * FROM calibration LIMIT 1")->fetch(PDO::FETCH_ASSOC);}?>
<form method="POST"><div class="two-col">
<div class="section"><div class="section-title">🌡️ NTC Термистор</div>
<div class="form-group"><label>Коэффициент B</label><input name="ntc_b" value="<?=$calib['ntc_b']??3950?>"></div>
<div class="form-group"><label>R25 (Ом при 25°C)</label><input name="ntc_r25" value="<?=$calib['ntc_r25']??10000?>"></div></div>
<div class="section"><div class="section-title">⚡ EC Калибровка</div>
<div class="form-group"><label>R1 (Ом)</label><input name="ec_r1" value="<?=$calib['ec_r1']??1000?>"></div>
<div class="form-group"><label>Темп. коэфф. (kT)</label><input name="ec_kt" value="<?=$calib['ec_kt']??0.02?>"></div>
<div class="form-group"><label>EC точка 1 (мС/см)</label><input name="ec_val_p1" value="<?=$calib['ec_val_p1']??1.413?>"></div>
<div class="form-group"><label>R2 точка 1 (Ом)</label><input name="ec_r2_p1" value="<?=$calib['ec_r2_p1']??''?>"></div>
<div class="form-group"><label>EC точка 2 (мС/см)</label><input name="ec_val_p2" value="<?=$calib['ec_val_p2']??2.76?>"></div>
<div class="form-group"><label>R2 точка 2 (Ом)</label><input name="ec_r2_p2" value="<?=$calib['ec_r2_p2']??''?>"></div>
<div class="form-group"><label>Коррекция EC</label><input name="ec_val_korr" value="<?=$calib['ec_val_korr']??0?>"></div></div></div>
<div class="section"><div class="section-title">⚗️ pH Калибровка (3 точки)</div><p style="color:#8b949e;margin-bottom:15px">Текущее RAW: <b style="color:#58a6ff"><?=$last['ph_mv']??'Н/Д'?></b> мВ</p>
<div class="two-col"><div>
<div class="form-group"><label>pH точка 1</label><input name="ph_val_p1" value="<?=$calib['ph_val_p1']??4?>"></div>
<div class="form-group"><label>RAW точка 1 (мВ)</label><input name="ph_raw_p1" value="<?=$calib['ph_raw_p1']??''?>"></div>
<div class="form-group"><label>pH точка 2</label><input name="ph_val_p2" value="<?=$calib['ph_val_p2']??7?>"></div>
<div class="form-group"><label>RAW точка 2 (мВ)</label><input name="ph_raw_p2" value="<?=$calib['ph_raw_p2']??''?>"></div></div><div>
<div class="form-group"><label>pH точка 3</label><input name="ph_val_p3" value="<?=$calib['ph_val_p3']??10?>"></div>
<div class="form-group"><label>RAW точка 3 (мВ)</label><input name="ph_raw_p3" value="<?=$calib['ph_raw_p3']??''?>"></div></div></div></div>
<button type="submit" name="save" class="btn btn-primary">💾 Сохранить</button></form>

<?php elseif($page==='pumps'):
if($_SERVER['REQUEST_METHOD']==='POST'&&isset($_POST['save'])){
$pdo->prepare("UPDATE pumps SET pump1=?,pump2=?,pump3=?,pump4=?,pump1_name=?,pump2_name=?,pump3_name=?,pump4_name=? WHERE id=1")->execute([isset($_POST['pump1'])?1:0,isset($_POST['pump2'])?1:0,isset($_POST['pump3'])?1:0,isset($_POST['pump4'])?1:0,$_POST['pump1_name'],$_POST['pump2_name'],$_POST['pump3_name'],$_POST['pump4_name']]);
echo'<div class="alert alert-success">✓ Сохранено!</div>';$pumps=$pdo->query("SELECT * FROM pumps LIMIT 1")->fetch(PDO::FETCH_ASSOC);}?>
<form method="POST"><div class="section"><div class="section-title">💧 Управление насосами</div>
<p style="color:#8b949e;margin-bottom:20px">Нажмите на карточку насоса чтобы переключить состояние, затем сохраните.</p>
<div class="pump-grid">
<?php for($i=1;$i<=4;$i++):?><label class="pump-card <?=($pumps["pump$i"]??0)?'active':''?>">
<input type="checkbox" name="pump<?=$i?>" <?=($pumps["pump$i"]??0)?'checked':''?> style="display:none" onchange="this.parentElement.classList.toggle('active');this.parentElement.querySelector('.pump-status').textContent=this.checked?'ВКЛ':'ВЫКЛ'">
<div class="pump-icon">💧</div><input name="pump<?=$i?>_name" value="<?=htmlspecialchars($pumps["pump{$i}_name"]??"Насос $i")?>" style="text-align:center;background:transparent;border:none;color:#c9d1d9;font-weight:bold;width:100%">
<div class="pump-status"><?=($pumps["pump$i"]??0)?'ВКЛ':'ВЫКЛ'?></div></label><?php endfor;?></div></div>
<button type="submit" name="save" class="btn btn-primary">💾 Сохранить</button></form>

<?php elseif($page==='history'):$limit=intval($_GET['limit']??50);$stmt=$pdo->query("SELECT * FROM readings ORDER BY created_at DESC LIMIT " . $limit);$h=$stmt->fetchAll(PDO::FETCH_ASSOC);?>
<div class="section"><div class="section-title">📊 История измерений</div>
<form method="GET" style="margin-bottom:20px"><input type="hidden" name="page" value="history">
<select name="limit" onchange="this.form.submit()" style="width:auto"><option value="50" <?=$limit==50?'selected':''?>>50 записей</option><option value="100" <?=$limit==100?'selected':''?>>100 записей</option><option value="500" <?=$limit==500?'selected':''?>>500 записей</option></select></form>
<?php if(empty($h)):?><div class="alert alert-info">Нет данных</div><?php else:?>
<div style="overflow-x:auto"><table><tr><th>Время</th><th>Корни</th><th>Воздух</th><th>Влаж.</th><th>pH</th><th>EC</th><th>Уров.</th><th>Сигнал</th></tr>
<?php foreach($h as $r):?><tr><td><?=$r['created_at']?></td><td><?=isset($r['root_temp'])?number_format($r['root_temp'],1):'-'?></td><td><?=isset($r['air_temp'])?number_format($r['air_temp'],1):'-'?></td><td><?=isset($r['air_hum'])?number_format($r['air_hum'],1):'-'?></td><td><?=isset($r['ph'])?number_format($r['ph'],2):'-'?></td><td><?=isset($r['ec'])?number_format($r['ec'],2):'-'?></td><td><?=isset($r['distance'])?number_format($r['distance'],1):'-'?></td><td><?=$r['rssi']??'-'?></td></tr><?php endforeach;?>
</table></div><?php endif;?></div>

<?php elseif($page==='logs'):
$logsLimit = intval($_GET['limit'] ?? 100);
$stmt = $pdo->prepare("SELECT * FROM logs WHERE device_id = 'wegabox' ORDER BY created_at DESC LIMIT ?");
$stmt->execute([$logsLimit]);
$logs = $stmt->fetchAll(PDO::FETCH_ASSOC);
?>
<div class="section">
    <div class="section-title" style="display:flex;justify-content:space-between;align-items:center;flex-wrap:wrap;gap:10px">
        <span>📋 Логи ESP32</span>
        <form method="GET" style="display:flex;gap:10px;align-items:center">
            <input type="hidden" name="page" value="logs">
            <select name="limit" onchange="this.form.submit()" style="width:auto">
                <option value="50" <?=$logsLimit==50?'selected':''?>>50</option>
                <option value="100" <?=$logsLimit==100?'selected':''?>>100</option>
                <option value="200" <?=$logsLimit==200?'selected':''?>>200</option>
                <option value="500" <?=$logsLimit==500?'selected':''?>>500</option>
            </select>
            <button type="button" onclick="location.reload()" class="btn btn-primary" style="padding:8px 15px">🔄 Обновить</button>
        </form>
    </div>
    <?php if(empty($logs)):?>
    <div class="alert alert-info">📭 Логов пока нет. ESP32 начнёт отправлять логи после обновления прошивки.</div>
    <?php else:?>
    <div style="background:#0d1117;border:1px solid #30363d;border-radius:6px;padding:15px;max-height:600px;overflow-y:auto;font-family:'Consolas',monospace;font-size:13px;">
        <?php foreach($logs as $log): 
            $color = '#8b949e';
            if($log['level'] === 'ERROR') $color = '#f85149';
            elseif($log['level'] === 'WARN') $color = '#d29922';
            elseif($log['level'] === 'INFO') $color = '#58a6ff';
            elseif($log['level'] === 'DEBUG') $color = '#8b949e';
        ?>
        <div style="margin-bottom:8px;padding-bottom:8px;border-bottom:1px solid #21262d;">
            <span style="color:#6e7681"><?=substr($log['created_at'], 11)?></span>
            <span style="color:<?=$color?>;font-weight:bold;margin:0 8px">[<?=$log['level']?>]</span>
            <span style="color:#c9d1d9"><?=htmlspecialchars($log['message'])?></span>
        </div>
        <?php endforeach;?>
    </div>
    <?php endif;?>
</div>
<?php endif;?>
</div>

<?php if($page==='dashboard' || $page==='charts'): ?>
<script>
const chartData = <?=json_encode($chartData)?>;
const period = '<?=$period?>';

const labels = chartData.map(r => {
    const d = new Date(r.created_at);
    if (period === 'hour') {
        return d.getHours().toString().padStart(2,'0') + ':' + d.getMinutes().toString().padStart(2,'0');
    } else if (period === 'day') {
        return d.getHours().toString().padStart(2,'0') + ':' + d.getMinutes().toString().padStart(2,'0');
    } else if (period === 'week') {
        return d.getDate() + '.' + (d.getMonth()+1) + ' ' + d.getHours() + 'ч';
    } else {
        return d.getDate() + '.' + (d.getMonth()+1);
    }
});

const rootTemp = chartData.map(r => r.root_temp);
const airTemp = chartData.map(r => r.air_temp);
const airHum = chartData.map(r => r.air_hum);
const ph = chartData.map(r => r.ph);
const ec = chartData.map(r => r.ec);
const level = chartData.map(r => r.distance);

const chartOptions = {
    responsive: true,
    maintainAspectRatio: false,
    spanGaps: true,
    interaction: { intersect: false, mode: 'index' },
    plugins: { 
        legend: { labels: { color: '#8b949e' } },
        tooltip: { backgroundColor: '#161b22', borderColor: '#30363d', borderWidth: 1 }
    },
    scales: {
        x: { ticks: { color: '#8b949e', maxTicksLimit: 12 }, grid: { color: '#21262d' } },
        y: { ticks: { color: '#8b949e' }, grid: { color: '#21262d' } }
    },
    elements: { 
        line: { tension: 0, borderWidth: 2, spanGaps: true },
        point: { radius: 0, hoverRadius: 0 }
    }
};

<?php if($page==='dashboard'): ?>
new Chart(document.getElementById('tempChart'), {
    type: 'line',
    data: {
        labels: labels,
        datasets: [
            { label: 'Корни °C', data: rootTemp, borderColor: '#f85149', fill: false },
            { label: 'Воздух °C', data: airTemp, borderColor: '#58a6ff', fill: false }
        ]
    },
    options: chartOptions
});

new Chart(document.getElementById('phEcChart'), {
    type: 'line',
    data: {
        labels: labels,
        datasets: [
            { label: 'pH', data: ph, borderColor: '#3fb950', fill: false, yAxisID: 'y' },
            { label: 'EC мС/см', data: ec, borderColor: '#d29922', fill: false, yAxisID: 'y1' }
        ]
    },
    options: {
        ...chartOptions,
        scales: {
            x: chartOptions.scales.x,
            y: { type: 'linear', position: 'left', ticks: { color: '#3fb950' }, grid: { color: '#21262d' } },
            y1: { type: 'linear', position: 'right', ticks: { color: '#d29922' }, grid: { drawOnChartArea: false } }
        }
    }
});
<?php endif; ?>

<?php if($page==='charts'): ?>
new Chart(document.getElementById('tempChartFull'), {
    type: 'line',
    data: {
        labels: labels,
        datasets: [
            { label: 'Корни °C', data: rootTemp, borderColor: '#f85149', fill: false },
            { label: 'Воздух °C', data: airTemp, borderColor: '#58a6ff', fill: false }
        ]
    },
    options: chartOptions
});

new Chart(document.getElementById('humChart'), {
    type: 'line',
    data: {
        labels: labels,
        datasets: [{ label: 'Влажность %', data: airHum, borderColor: '#58a6ff', fill: false }]
    },
    options: chartOptions
});

new Chart(document.getElementById('phChart'), {
    type: 'line',
    data: {
        labels: labels,
        datasets: [{ label: 'pH', data: ph, borderColor: '#3fb950', fill: false }]
    },
    options: {...chartOptions, scales: {...chartOptions.scales, y: { min: 3, max: 11, ticks: { color: '#8b949e' }, grid: { color: '#21262d' } }}}
});

new Chart(document.getElementById('ecChart'), {
    type: 'line',
    data: {
        labels: labels,
        datasets: [{ label: 'EC мС/см', data: ec, borderColor: '#d29922', fill: false }]
    },
    options: chartOptions
});

new Chart(document.getElementById('levelChart'), {
    type: 'line',
    data: {
        labels: labels,
        datasets: [{ label: 'Уровень см', data: level, borderColor: '#a371f7', fill: false }]
    },
    options: chartOptions
});
<?php endif; ?>
</script>
<?php endif; ?>

<?php if($page==='dashboard'):?><script>setTimeout(()=>location.reload(),30000)</script><?php endif;?>
</body></html>
