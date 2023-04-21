# -*- coding: utf-8 -*-
"""
Created on Wed Apr 20 19:38:31 2022

iotlab432wifi
labiot
@author: Dawid
"""

from http.server import BaseHTTPRequestHandler, HTTPServer
import os
import json

class handler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()
        
        if os.path.basename(self.path) == 'led1':
            self.wfile.write("1".encode('utf-8'))
               
    def do_POST(self):
            
        file_length = int(self.headers['Content-Length'])
        if os.path.basename(self.path) == 'temp':
            rx = json.loads(self.rfile.read(file_length))
            print(f"TEMP:{rx['t1']}")
        
        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()
    

# with HTTPServer(('192.168.1.158', 8000), handler) as server:
with HTTPServer(('192.168.100.140', 8001), handler) as server:
    server.serve_forever()
    
    