
import openai

openai.api_key = "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"

while True:
    prompt = input("You: ")
    if prompt.lower() in ["exit", "quit"]:
        break
    response = openai.ChatCompletion.create(
        model="gpt-5",
        messages=[{"role": "user", "content": prompt}]
    )
    print("GPT:", response.choices[0].message["content"])
