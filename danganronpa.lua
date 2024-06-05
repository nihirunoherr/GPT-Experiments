-- Danganronpa Text Adventure
local term = require("term")
local event = require("event")
local computer = require("computer")

-- Clear the screen
term.clear()

-- Utility function to print text slowly
local function slowPrint(text)
    for i = 1, #text do
        io.write(text:sub(i, i))
        os.sleep(0.05)
    end
    io.write("\n")
end

-- Introduction
slowPrint("Welcome to Danganronpa: Text Adventure!")
slowPrint("You find yourself in a strange school with other students...")
slowPrint("A mysterious bear named Monokuma appears and tells you that you must kill to escape.")
slowPrint("What will you do?")

-- Character definitions
local characters = {
    {name = "Kyoko", description = "A stoic and intelligent girl."},
    {name = "Makoto", description = "A hopeful and determined boy."},
    {name = "Byakuya", description = "An arrogant and wealthy young man."},
}

-- Display characters
slowPrint("\nCharacters:")
for i, character in ipairs(characters) do
    slowPrint(i .. ". " .. character.name .. " - " .. character.description)
end

-- Game choices
local function makeChoice()
    slowPrint("\nWhat will you do?")
    slowPrint("1. Talk to Kyoko")
    slowPrint("2. Talk to Makoto")
    slowPrint("3. Talk to Byakuya")
    slowPrint("4. Explore the school")

    local choice
    repeat
        io.write("> ")
        choice = tonumber(io.read())
    until choice >= 1 and choice <= 4

    return choice
end

-- Main game loop
local function gameLoop()
    local running = true
    while running do
        local choice = makeChoice()

        if choice == 1 then
            slowPrint("\nYou approach Kyoko...")
            slowPrint("Kyoko: 'We need to find a way out of here without falling into Monokuma's trap.'")
        elseif choice == 2 then
            slowPrint("\nYou talk to Makoto...")
            slowPrint("Makoto: 'Stay hopeful, we can get through this together!'")
        elseif choice == 3 then
            slowPrint("\nYou approach Byakuya...")
            slowPrint("Byakuya: 'Don't get in my way if you want to survive.'")
        elseif choice == 4 then
            slowPrint("\nYou explore the school and find a clue!")
            slowPrint("It's a keycard to the principal's office.")
            slowPrint("You gather everyone and decide to confront Monokuma in the principal's office.")
            slowPrint("You manage to outsmart Monokuma and escape the school together!")
            running = false
        end
    end

    slowPrint("\nCongratulations! You've escaped the school!")
end

-- Start the game
gameLoop()
