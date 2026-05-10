import re

# --- Helper: Intent Detection ---
def detect_intent(user_input):
    user_input = user_input.lower()

    if any(word in user_input for word in ["hi", "hello", "hey"]):
        return "greeting"
    elif any(word in user_input for word in ["casual", "friends", "daily"]):
        return "casual"
    elif any(word in user_input for word in ["party", "club", "formal"]):
        return "party"
    elif any(word in user_input for word in ["size", "fit", "measurement"]):
        return "size"
    elif any(word in user_input for word in ["order", "track", "status"]):
        return "order"
    elif any(word in user_input for word in ["delivery", "shipping"]):
        return "delivery"
    elif any(word in user_input for word in ["exit", "bye", "quit"]):
        return "exit"
    else:
        return "unknown"


# --- Outfit Functions ---
def casual_outfits():
    print("\nBot: Here are some casual outfit ideas 😊\n")

    print("👉 Outfit 1:")
    print("• White oversized t-shirt")
    print("• Light blue denim jeans")
    print("• White sneakers\n")

    print("👉 Outfit 2:")
    print("• Pastel hoodie")
    print("• Black joggers")
    print("• Chunky sneakers\n")

    print("👉 Outfit 3:")
    print("• Floral shirt")
    print("• Beige chinos")
    print("• Slip-on shoes\n")


def party_outfits():
    print("\nBot: Here are some party outfit ideas 🔥\n")

    print("👉 Outfit 1:")
    print("• Black fitted dress")
    print("• Heels")
    print("• Statement earrings\n")

    print("👉 Outfit 2:")
    print("• Leather jacket")
    print("• Crop top")
    print("• High-waisted jeans\n")

    print("👉 Outfit 3:")
    print("• Shimmer top")
    print("• Mini skirt")
    print("• Strappy heels\n")


def size_help():
    print("\nBot: I can help with sizing 😊")
    height = input("Bot: What's your height? ")
    size = input("Bot: What size do you usually wear? ")

    print("\nBot: Based on your input:")
    print("• Tops: Go with your regular size (" + size + ")")
    print("• Bottoms: Check waist measurements for best fit\n")

    print("Bot: Suggested outfits in your size:\n")

    print("👉 Outfit 1:")
    print("• Regular fit t-shirt")
    print("• Slim fit jeans\n")

    print("👉 Outfit 2:")
    print("• Relaxed fit shirt")
    print("• Straight trousers\n")

    print("👉 Outfit 3:")
    print("• Oversized sweatshirt")
    print("• Joggers\n")


def order_status():
    order_id = input("Bot: Please enter your order ID: ")
    print(f"Bot: Order {order_id} is out for delivery 🚚 (arriving in 1–2 days)\n")

    print("Bot: Meanwhile, check these styles:\n")

    print("👉 Outfit 1:")
    print("• Denim jacket")
    print("• White t-shirt")
    print("• Black jeans\n")

    print("👉 Outfit 2:")
    print("• Polo t-shirt")
    print("• Chinos")
    print("• Sneakers\n")

    print("👉 Outfit 3:")
    print("• Kurta")
    print("• Slim pants")
    print("• Ethnic sandals\n")


def delivery_info():
    print("Bot: Delivery takes 2–5 business days depending on your location 🚚")


# --- Main Chatbot ---
def fashion_chatbot():
    print("Fashion Bot: Welcome to StyleMate - Your Fashion Assistant!")
    print("Bot: Ask me about outfits, sizes, or orders. Type 'exit' to quit.\n")

    while True:
        user_input = input("You: ")
        intent = detect_intent(user_input)

        if intent == "exit":
            print("Bot: Stay stylish! Goodbye ✨")
            break

        elif intent == "greeting":
            print("Bot: Hi! What are you looking for today? Casual or party outfit?")

        elif intent == "casual":
            print("Bot: Great choice! Casual looks are always comfy 😄")
            casual_outfits()

        elif intent == "party":
            print("Bot: Let's get you party-ready 🎉")
            party_outfits()

        elif intent == "size":
            size_help()

        elif intent == "order":
            order_status()

        elif intent == "delivery":
            delivery_info()

        else:
            print("Bot: I didn’t understand that.")
            print("Bot: Try asking about casual, party, size, or orders.\n")


# Run the chatbot
fashion_chatbot()

'''
┌──(vmsin0㉿martian)-[~/STUDY/Manual/AI]
└─$  python3 Prac5.py
Fashion Bot: Welcome to StyleMate - Your Fashion Assistant!
Bot: Ask me about outfits, sizes, or orders. Type 'exit' to quit.

You: Hi
Bot: Hi! What are you looking for today? Casual or party outfit?
You: Casual
Bot: Great choice! Casual looks are always comfy 😄

Bot: Here are some casual outfit ideas 😊

👉 Outfit 1:
• White oversized t-shirt
• Light blue denim jeans
• White sneakers

👉 Outfit 2:
• Pastel hoodie
• Black joggers
• Chunky sneakers

👉 Outfit 3:
• Floral shirt
• Beige chinos
• Slip-on shoes

You: Outfit 1

Bot: I can help with sizing 😊
Bot: What's your height? 165cm
Bot: What size do you usually wear? 32

Bot: Based on your input:
• Tops: Go with your regular size (32)
• Bottoms: Check waist measurements for best fit

Bot: Suggested outfits in your size:

👉 Outfit 1:
• Regular fit t-shirt
• Slim fit jeans

👉 Outfit 2:
• Relaxed fit shirt
• Straight trousers

👉 Outfit 3:
• Oversized sweatshirt
• Joggers

You: Thank You
Bot: I didn’t understand that.
Bot: Try asking about casual, party, size, or orders.

You: Orders
Bot: Please enter your order ID: ORD123
Bot: Order ORD123 is out for delivery 🚚 (arriving in 1–2 days)

Bot: Meanwhile, check these styles:

👉 Outfit 1:
• Denim jacket
• White t-shirt
• Black jeans

👉 Outfit 2:
• Polo t-shirt
• Chinos
• Sneakers

👉 Outfit 3:
• Kurta
• Slim pants
• Ethnic sandals

You: Outfit 3

Bot: I can help with sizing 😊
Bot: What's your height? 180cm
Bot: What size do you usually wear? 32

Bot: Based on your input:
• Tops: Go with your regular size (32)
• Bottoms: Check waist measurements for best fit

Bot: Suggested outfits in your size:

👉 Outfit 1:
• Regular fit t-shirt
• Slim fit jeans

👉 Outfit 2:
• Relaxed fit shirt
• Straight trousers

👉 Outfit 3:
• Oversized sweatshirt
• Joggers

You: exit
Bot: Stay stylish! Goodbye ✨


'''
