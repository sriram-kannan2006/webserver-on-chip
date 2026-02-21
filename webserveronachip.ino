#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "RAM_Server";
const char* password = "12345678";

ESP8266WebServer server(80);

/* ----------- Login Page ----------- */
void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ESP8266 Secure Login</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      * {
        box-sizing: border-box;
        margin: 0;
        padding: 0;
        font-family: 'Segoe UI', sans-serif;
      }

      body {
        height: 100vh;
        display: flex;
        justify-content: center;
        align-items: center;
        background: linear-gradient(135deg, #1f4037, #99f2c8);
      }

      .login-box {
        width: 320px;
        padding: 30px;
        border-radius: 15px;
        background: rgba(255, 255, 255, 0.15);
        backdrop-filter: blur(15px);
        box-shadow: 0 8px 32px rgba(0, 0, 0, 0.3);
        color: white;
        text-align: center;
      }

      .login-box h2 {
        margin-bottom: 20px;
        font-weight: 500;
      }

      .input-group {
        margin-bottom: 15px;
      }

      input {
        width: 100%;
        padding: 12px;
        border-radius: 8px;
        border: none;
        outline: none;
        font-size: 14px;
      }

      input[type="text"],
      input[type="password"] {
        background: rgba(255, 255, 255, 0.9);
      }

      input[type="text"]:focus,
      input[type="password"]:focus {
        border: 2px solid #00f2fe;
      }

      input[type="submit"] {
        margin-top: 10px;
        background: linear-gradient(45deg, #00f2fe, #4facfe);
        color: white;
        font-weight: bold;
        cursor: pointer;
        transition: 0.3s ease;
      }

      input[type="submit"]:hover {
        transform: scale(1.05);
        box-shadow: 0 4px 15px rgba(0, 242, 254, 0.6);
      }

      .footer {
        margin-top: 15px;
        font-size: 12px;
        opacity: 0.8;
      }
    </style>
  </head>
  <body>
    <div class="login-box">
      <h2>Secure Login</h2>
      <form action="/login" method="POST">
        <div class="input-group">
          <input type="text" name="username" placeholder="Username" required>
        </div>
        <div class="input-group">
          <input type="password" name="password" placeholder="Password" required>
        </div>
        <input type="submit" value="LOGIN">
      </form>
      <div class="footer">
        ESP8266 Web Server
      </div>
    </div>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

/* ----------- Login Handler ----------- */
void handleLogin() {
  if (server.hasArg("username") && server.hasArg("password")) {
    String user = server.arg("username");
    String pass = server.arg("password");

    if (user == "admin" && pass == "1234") {
      server.send(200, "text/html", "<h1 style='text-align:center;'>Login Successful</h1>");
    } else {
      server.send(200, "text/html", "<h1 style='text-align:center;'>Login Failed</h1><div style='text-align:center;'><a href='/'>Try Again</a></div>");
    }
  } else {
    server.send(400, "text/html", "Bad Request");
  }
}

void setup() {
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/login", HTTP_POST, handleLogin);

  server.begin();
}

void loop() {
  server.handleClient();
}
