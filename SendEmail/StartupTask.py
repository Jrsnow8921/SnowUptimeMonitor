import smtplib
import os, sys
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email import encoders

filename = "\\\\Asus-pc\\asus_share\\textfile.txt"

def check_server_message():
  if 'DOWN' in open(filename).read():
    send_email()
  else:
     print "no servers down"



def send_email(): 
    fromaddr = "@gmail.com"
    toaddr = "@gmail.com"
 
    msg = MIMEMultipart()
 
    msg['From'] = fromaddr
    msg['To'] = toaddr
    msg['Subject'] = "Server DOWN!!!"
 
    body = "Server IS DOWN!!!!"
 
    msg.attach(MIMEText(body, 'plain'))
 
    attachment = open(filename, "rb")
 
    part = MIMEBase('application', 'octet-stream')
    part.set_payload((attachment).read())
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', "attachment; filename= %s" % filename)
 
    msg.attach(part)
 
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(fromaddr, "pass")
    text = msg.as_string()
    server.sendmail(fromaddr, toaddr, text)
    server.quit()

check_server_message()
