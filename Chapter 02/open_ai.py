from flask import Flask, render_template, request
import openai

app = Flask(__name__)

# Set your OpenAI API key here
openai.api_key = YOUR-API-KEY'

@app.route('/')
def index():
    return render_template('index.html', chat_history="")

@app.route('/chat', methods=['POST'])
def chat():
    user_message = request.form['user_message']
    chat_history = request.form['chat_history']

    # Append the user's message to the chat history
    chat_history += f"You: {user_message}\n"

    # Make an API call to ChatGPT
    response = openai.chat.completion.create(
        engine="gpt-3.5-turbo",  # Or another engine like "text-davinci-003"
        prompt=chat_history,
        max_tokens=50
    )

    # Append ChatGPT's reply to the chat history
    chat_history += f"ChatGPT: {response.choices[0].text.strip()}\n"

    return render_template('index.html', chat_history=chat_history)

if __name__ == '__main__':
    app.run(host='YOUR-IP-ADDRESS', port=8080)
