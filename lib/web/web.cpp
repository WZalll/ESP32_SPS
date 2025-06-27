#include "web.h"
#include <WiFi.h>
#include <WebServer.h>
#include "L298N.h" // 引入电机控制库
#include "oled.h"

WebServer server(80);

void web_init();
void web_handleClient();
void handleCarControl();
void handleRoot();

void handleRoot() {
    String html = "<html><head><style>";
    html += "body { width: 300px; margin: auto; text-align: center; font-family: Arial, sans-serif; background: linear-gradient(to bottom, #e6f7ff, #b3d9ff); }";
    html += "button { width: 120px; height: 120px; margin: 15px; font-size: 18px; border-radius: 20px; background: linear-gradient(to bottom, #c8e6c9, #a5d6a7); }";
    html += "input[type='range'] { width: 200px; margin-top: 20px; }";
    html += ".controls { display: flex; flex-direction: column; align-items: center; gap: 15px; }";
    html += "#debugConsole { width: 100%; height: 100px; overflow-y: auto; border: 1px solid #ccc; margin-top: 20px; padding: 10px; background: #f9f9f9; font-family: monospace; }"; // 新增：调试框样式
    html += "</style></head><body>";
    html += "<h1>Control Panel</h1>";
    html += "<div class='controls'>";
    html += "<button onclick='sendCommand(\"forward\")'>Forward</button>";
    html += "<div style='display: flex; gap: 15px;'>";
    html += "<button onclick='sendCommand(\"left\")'>Left</button>";
    html += "<button onclick='sendCommand(\"backward\")'>Backward</button>";
    html += "<button onclick='sendCommand(\"right\")'>Right</button>";
    html += "</div>";
    html += "<button onclick='sendCommand(\"stop\")'>Stop</button>";
    html += "</div>";
    html += "<p>Speed: <input type='range' id='speed' min='0' max='255' value='100'> <span id='speedValue'>100</span></p>";
    html += "<div id='debugConsole'></div>"; // 新增：调试信息显示框
    html += "<script>";
    html += "var speedSlider = document.getElementById('speed');";
    html += "var speedValue = document.getElementById('speedValue');";
    html += "speedValue.innerHTML = speedSlider.value;";
    html += "speedSlider.oninput = function() { speedValue.innerHTML = this.value; };";
    html += "function sendCommand(action) {";
    html += "  var speed = document.getElementById('speed').value;";
    html += "  fetch('/car?action=' + action + '&speed=' + speed)";
    html += "    .then(response => response.text())";
    html += "    .then(data => {";
    html += "      var debugConsole = document.getElementById('debugConsole');";
    html += "      debugConsole.innerHTML += data + '<br>';"; // 新增：动态更新调试信息
    html += "      if (debugConsole.scrollHeight > debugConsole.clientHeight) {";
    html += "        debugConsole.scrollTop = debugConsole.scrollHeight;"; // 自动滚动到底部
    html += "      }";
    html += "    })";
    html += "    .catch(error => console.error('Error:', error));";
    html += "}";
    html += "</script>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleCarControl() {
    if (server.hasArg("action") && server.hasArg("speed")) {
        String action = server.arg("action");
        int speed = server.arg("speed").toInt();

        extern L298N motor;

        String responseMessage = ""; // 新增：定义响应信息
        if (action == "forward") {
            moveForward(&motor, speed);
            responseMessage = "Moving forward at speed " + String(speed);
        } else if (action == "backward") {
            moveBackward(&motor, speed);
            responseMessage = "Moving backward at speed " + String(speed);
        } else if (action == "left") {
            turnLeft(&motor, speed);
            responseMessage = "Turning left at speed " + String(speed);
        } else if (action == "right") {
            turnRight(&motor, speed);
            responseMessage = "Turning right at speed " + String(speed);
        } else if (action == "stop") {
            stop();
            responseMessage = "Car stopped";
        } else {
            server.send(400, "text/plain", "Bad Request: Invalid 'action' parameter");
            return;
        }

        server.send(200, "text/plain", responseMessage); // 返回运行信息
    } else {
        server.send(400, "text/plain", "Bad Request: Missing 'action' or 'speed' parameter");
    }
}

void web_init() {
    // 初始化 WiFi 连接
    WiFi.begin("OP11", "88888888");
    Terminal_WriteLine("AP:OP11");
    Terminal_WriteLine("PAS:88888888");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Terminal_WriteLine("Connected to WiFi");
    // 设置路由
    server.on("/", handleRoot);
    server.on("/car", handleCarControl); // 新增：注册小车控制路由

    // 启动服务器
    server.begin();
    Serial.println("HTTP server started");
    Terminal_WriteLine("Web server started");
        // 新增：输出设备的 IP 地址到串口
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Terminal_WriteLine(WiFi.localIP().toString().c_str());
    
}

void web_handleClient() {
    server.handleClient();
}

