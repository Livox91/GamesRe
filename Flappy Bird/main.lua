push =require 'push'

Class = require 'class'

require'Bird'
require'Pipe'
require'Pipepairs'

require 'StateMachine'
require 'states/BaseState'
require 'states/TitleScreen'
require 'states/PlayState'
require 'states/Score'
require 'states/Countdown'

WINDOW_HEIGHT=720
WINDOW_WIDTH=1280

VIRTUAL_WIDTH=512
VIRTUAL_HEIGHT=288

local background = love.graphics.newImage('images/background.png')
local backgroundScroll=0

local ground = love.graphics.newImage('images/ground.png')
local groundScroll=0

local BACKGROUND_SCROLL_SPEED= 30
local GROUND_SCROLL_SPEED= 60

local BACKGROUND_LOOPING_POINT=413
local scrolling=true


function love.load()
    love.graphics.setDefaultFilter('nearest', 'nearest')
    math.randomseed(os.time())
    love.window.setTitle('FlappyBird')

    smallFont =love.graphics.newFont('fonts/font.ttf',8)
    medFont =love.graphics.newFont('fonts/flappy.ttf',14)
    flappyFont =love.graphics.newFont('fonts/flappy.ttf',28)
    scoreFont =love.graphics.newFont('fonts/flappy.ttf',56)
    love.graphics.setFont(flappyFont)

    sound = {
        ['jump'] = love.audio.newSource('sounds/fart.wav','static'),
        ['explosion'] = love.audio.newSource('sounds/exp.wav','static'),
        ['score'] = love.audio.newSource('sounds/wow.wav','static'),
        --['music'] = love.audio.newSource('sounds/song.wav','static')
    }

    --sound['music']:setLooping(true)
    --sound['music']:play()

    push:setupScreen(VIRTUAL_WIDTH,VIRTUAL_HEIGHT,WINDOW_WIDTH,WINDOW_HEIGHT,{
        vsync=true,
        fullscreen=false,
        resizable=true
    })

    gStateMachine=StateMachine{
        ['title'] = function ()return TitleScreen()    end,
        ['count'] = function ()return CountDown()      end,
        ['play'] = function () return PlayState()      end,
        ['score'] = function () return Score()         end
    }
    gStateMachine:change('title')

    love.keyboard.keysPressed={}
    
end

function love.resize(w,h)
    push:resize(w,h)
    
end

function love.keypressed(key)
    love.keyboard.keysPressed[key]=true
    if key=='escape' then
        love.event.quit()
    end
    
end

function love.keyboard.wasPressed(key)
    if love.keyboard.keysPressed[key] then
        return true
    else
        return false
    end
    
end

function love.keyboard.isStraight(key)
    return false
    
end

function love.update(dt)

    backgroundScroll=(backgroundScroll+BACKGROUND_SCROLL_SPEED*dt)
    % BACKGROUND_LOOPING_POINT
    groundScroll= (groundScroll+GROUND_SCROLL_SPEED*dt)
    % VIRTUAL_WIDTH

    gStateMachine:update(dt)
    
    love.keyboard.keysPressed={}

end

function love.draw()
    push:start()
    love.graphics.draw(background,-backgroundScroll,0)
    gStateMachine:render()
    love.graphics.draw(ground,-groundScroll,VIRTUAL_HEIGHT-16)
    
    push:finish()
    
end