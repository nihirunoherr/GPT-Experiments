local component = require("component")
local term = require("term")
local event = require("event")

-- Set up the screen and GPU
local gpu = component.gpu
local screen = component.screen

-- Set resolution
local width, height = gpu.maxResolution()
gpu.setResolution(width, height)

-- Colors
local backgroundColor = 0x000000 -- black
local textColor = 0x00FF00 -- green

-- Set up the screen
gpu.setBackground(backgroundColor)
gpu.setForeground(textColor)
term.clear()

-- Characters to display
local characters = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"}

-- Helper function to get a random character
local function getRandomCharacter()
    return characters[math.random(1, #characters)]
end

-- Initialize columns
local columns = {}
for x = 1, width do
    columns[x] = math.random(1, height)
end

-- Main loop
while true do
    for x = 1, width do
        local y = columns[x]
        
        -- Clear the character that was here
        gpu.set(x, y, " ")
        
        -- Move up
        y = y - 1
        if y < 1 then
            y = height
        end
        
        -- Draw a new character
        gpu.set(x, y, getRandomCharacter())
        
        -- Save the new position
        columns[x] = y
    end
    
    -- Small delay to control speed
    os.sleep(0.05)
    
    -- Check for user interrupt (Ctrl + C)
    if event.pull(0, "interrupted") then
        term.clear()
        print("Matrix effect stopped.")
        break
    end
end
