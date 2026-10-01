import pyautogui
import keyboard
import time

try:
    print("Move your mouse to the target and press Z to grab pixel info...")

    # Wait for the user to press 'z' and grab the position/color
    while True:
        if keyboard.is_pressed('z'):
            x, y = pyautogui.position()
            target_color = pyautogui.screenshot().getpixel((x, y))
            print(f"Target position: ({x}, {y})")
            print(f"Target color: {target_color}")
            break

    print("Now watching that pixel... waiting for color match...")

    # Wait for color to change
    while True:
        current_color = pyautogui.screenshot().getpixel((x, y))
        if current_color == target_color:
            start = time.time()

            # Click at the coordinates
            pyautogui.click(x, y)

            end = time.time()
            reaction_time = (end - start) * 1000  # Convert to milliseconds
            print(f"Clicked! Reaction time: {reaction_time:.2f} ms")
            break  # Remove this if you want it to keep running

except Exception as e:
    print(f"\n[ERROR] {e}\n")

finally:
    input("\nPress Enter to exit...")