import sys
import time
from dotenv import Dotenv
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS

# Load environment file
dotenv = Dotenv('.env')

# Fetch token from environment variables
token = dotenv["INFLUXDB_TOKEN"]
org = "YOUR_ORG"
url = "http://YOUR_IP:8086"

# Initialize InfluxDB client
write_client = InfluxDBClient(url=url, token=token, org=org)

# Specify bucket
bucket = "YOUR_BUCKET"

# Initialize write API
write_api = write_client.write_api(write_options=SYNCHRONOUS)

# Command-line arguments
if len(sys.argv) != 3:
    print("Usage: python script.py <field_value> <tag_value>")
    sys.exit(1)

value = int(sys.argv[1])
tag_value = sys.argv[2]

# Writing data points
point = (
    Point("temp_sensor")
    .tag("location", tag_value)
    .field("temp", value)
)
write_api.write(bucket=bucket, org=org, record=point)
