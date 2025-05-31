import os
import sys
import smtplib
from email.mime.text import MIMEText
from dotenv import load_dotenv

# Load environment variables from a .env file
load_dotenv()

def send_email(subject, body, to_email):
    # Create a MIMEText object with the email body
    msg = MIMEText(body)

    # Set the subject, sender, and recipient
    msg["Subject"] = subject
    msg["From"] = os.getenv("SMTP_USERNAME")
    msg["To"] = to_email

    # Connect to the SMTP server
    with smtplib.SMTP(os.getenv("SMTP_SERVER"), int(os.getenv("SMTP_PORT"))) as server:
        # Login to the SMTP server (if required)
     #   server.login(os.getenv("SMTP_USERNAME"), os.getenv("SMTP_PASSWORD"))

        # Send the email
        server.sendmail(os.getenv("SMTP_USERNAME"), to_email, msg.as_string())

    print("Email sent successfully to", to_email)

if __name__ == "__main__":
    # Check if all command line arguments are provided
    if len(sys.argv) != 4:
        print("Usage: python script.py <subject> <body> <destination_email>")
        sys.exit(1)

    # Extract command line arguments
    subject = sys.argv[1]
    body = sys.argv[2]
    to_email = sys.argv[3]

    # Send the email
    send_email(subject, body, to_email)
