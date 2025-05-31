#filename coap_relay_control.py
import logging
import argparse
import asyncio
from aiocoap import *

logging.basicConfig(level=logging.INFO)

async def set_relay_state(state):
    context = await Context.create_client_context()

    relay_request = Message(code=PUT, uri=f'coap://<ip-of-server>/actuators/relay', payload=str(state).encode())

    try:
        response = await context.request(relay_request).response
    except Exception as error:
        print('Failed to set relay state:')
        print(f"Encountered error: {error}")
    else:
        print('Relay state set successfully.')
        print('Response: %s\n%r' % (response.code, response.payload))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Set the value of the relay resource (0 or 1).')
    parser.add_argument('state', metavar='state', type=int, choices=[0, 1], help='Value for the relay (0 or 1)')

    args = parser.parse_args()

    asyncio.run(set_relay_state(args.state))
