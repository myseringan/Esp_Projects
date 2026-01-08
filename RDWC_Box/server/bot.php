<?php
/**
 * RDWC Box Telegram Bot
 * Monitoring and control via Telegram
 */

$BOT_TOKEN = "YOUR_BOT_TOKEN";  // Get from @BotFather
$CHAT_IDS = ["YOUR_CHAT_ID"];   // Your Telegram user ID

$DB_HOST = 'localhost';
$DB_NAME = 'wegabox';
$DB_USER = 'wegabox';
$DB_PASS = 'YOUR_PASSWORD';

try {
    $pdo = new PDO("mysql:host=$DB_HOST;dbname=$DB_NAME;charset=utf8mb4", $DB_USER, $DB_PASS);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die("DB Error");
}

function getLastData($pdo) {
    $stmt = $pdo->query("SELECT * FROM readings WHERE device_id = 'wegabox' ORDER BY created_at DESC LIMIT 1");
    return $stmt->fetch(PDO::FETCH_ASSOC);
}

function getPumps($pdo) {
    $stmt = $pdo->query("SELECT * FROM pumps LIMIT 1");
    return $stmt->fetch(PDO::FETCH_ASSOC);
}

function getLogs($pdo) {
    $stmt = $pdo->query("SELECT * FROM logs WHERE device_id = 'wegabox' ORDER BY created_at DESC LIMIT 10");
    return $stmt->fetchAll(PDO::FETCH_ASSOC);
}

function formatStatus($data) {
    if (!$data) return "❌ Нет данных";
    
    $time = date('d.m.Y H:i:s', strtotime($data['created_at']));
    $isOnline = (time() - strtotime($data['created_at'])) < 120;
    $status = $isOnline ? "🟢 Online" : "🔴 Offline";
    
    $msg = "📅 $time | $status\n\n";
    $msg .= "💧 <b>Раствор:</b>\n";
    $msg .= "EC: " . ($data['ec'] ? number_format($data['ec'], 2) . " мС/см" : '--') . "\n";
    $msg .= "pH: " . ($data['ph'] ? number_format($data['ph'], 2) : '--') . "\n\n";
    $msg .= "🌡 <b>Температуры:</b>\n";
    $msg .= "Корни: " . ($data['root_temp'] ? number_format($data['root_temp'], 1) . "°C" : '--') . "\n";
    $msg .= "Воздух: " . ($data['air_temp'] ? number_format($data['air_temp'], 1) . "°C" : '--') . "\n\n";
    $msg .= "💨 Влажность: " . ($data['air_hum'] ? number_format($data['air_hum'], 1) . "%" : '--') . "\n";
    $msg .= "📶 RSSI: " . ($data['rssi'] ?? '--') . " dBm";
    
    return $msg;
}

function formatPumps($pumps) {
    $msg = "💧 <b>Насосы:</b>\n\n";
    for ($i = 1; $i <= 4; $i++) {
        $name = $pumps["pump{$i}_name"] ?? "Насос $i";
        $state = ($pumps["pump$i"] ?? 0) ? "🟢 ВКЛ" : "⚪ ВЫКЛ";
        $msg .= "$name: $state\n";
    }
    return $msg;
}

function formatLogs($logs) {
    $msg = "📋 <b>Последние логи:</b>\n\n";
    if (empty($logs)) {
        $msg .= "Логов нет";
    } else {
        foreach ($logs as $log) {
            $time = substr($log['created_at'], 11, 8);
            $level = $log['level'];
            $emoji = $level === 'ERROR' ? '🔴' : ($level === 'WARN' ? '🟡' : '🔵');
            $msg .= "$emoji $time {$log['message']}\n";
        }
    }
    return $msg;
}

function sendTelegram($token, $chatId, $text, $keyboard = null) {
    $url = "https://api.telegram.org/bot$token/sendMessage";
    $params = [
        'chat_id' => $chatId,
        'text' => $text,
        'parse_mode' => 'HTML'
    ];
    if ($keyboard) {
        $params['reply_markup'] = json_encode($keyboard);
    }
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $params);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $result = curl_exec($ch);
    curl_close($ch);
    return json_decode($result, true);
}

function getKeyboard() {
    return [
        'keyboard' => [
            [['text' => '📊 Статус'], ['text' => '💧 Насосы']],
            [['text' => '📋 Логи'], ['text' => '⚙️ Веб']]
        ],
        'resize_keyboard' => true
    ];
}

// Webhook mode
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $input = file_get_contents('php://input');
    $update = json_decode($input, true);
    
    if (isset($update['message'])) {
        $chatId = $update['message']['chat']['id'];
        $text = $update['message']['text'] ?? '';
        
        // Access check
        if (!in_array($chatId, array_map('intval', $CHAT_IDS))) {
            sendTelegram($BOT_TOKEN, $chatId, "⛔ Доступ запрещён");
            exit;
        }
        
        $keyboard = getKeyboard();
        
        switch ($text) {
            case '/start':
            case '📊 Статус':
                $data = getLastData($pdo);
                $msg = formatStatus($data);
                break;
                
            case '💧 Насосы':
                $pumps = getPumps($pdo);
                $msg = formatPumps($pumps);
                break;
                
            case '📋 Логи':
                $logs = getLogs($pdo);
                $msg = formatLogs($logs);
                break;
                
            case '⚙️ Веб':
                $msg = "⚙️ <b>Веб-интерфейс:</b>\n\n";
                $msg .= "🌐 http://YOUR_DOMAIN/\n";
                $msg .= "🔒 https://YOUR_DOMAIN/";
                break;
                
            default:
                $msg = "❓ Используйте кнопки меню";
        }
        
        sendTelegram($BOT_TOKEN, $chatId, $msg, $keyboard);
    }
    exit;
}

// CLI mode - send status to all users
$data = getLastData($pdo);
$msg = formatStatus($data);
$keyboard = getKeyboard();

foreach ($CHAT_IDS as $chatId) {
    $result = sendTelegram($BOT_TOKEN, $chatId, $msg, $keyboard);
    echo "Sent to $chatId: " . ($result['ok'] ? 'OK' : 'FAIL') . "\n";
}
