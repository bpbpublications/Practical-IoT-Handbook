# filename coap_relay_state_getter.py
import logging
import asyncio
from aiocoap import *

logging.basicConfig(level=logging.INFO)

async def get_relay_state():
    context = await Context.create_client_context()

    relay_request = Message(code=GET, uri='coap://<ip-of-server>/actuators/relay')

    try:
        response = await context.request(relay_request).response
    except Exception as error:
        print('Failed to retrieve relay state:')
        print(f"Encountered error: {error}")
    else:
        print('Relay state retrieved successfully.')
        print('State: %s\n%r' % (response.code, response.payload.decode('utf-8')))

if __name__ == "__main__":
    asyncio.run(get_relay_state())
