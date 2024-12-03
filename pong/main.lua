
push = require 'push'
Class = require 'Class'
require 'Ball'
require 'paddle'
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

VIRTUAL_HEIGHT = 243 
VIRTUAL_WIDTH = 432
Paddle_Speed= 200


function love.load()
    love.graphics.setDefaultFilter('nearest','nearest')
    push:setupScreen(VIRTUAL_WIDTH,VIRTUAL_HEIGHT,WINDOW_WIDTH,WINDOW_HEIGHT,{
    fullscreen = false,
    resizable = false,
    vsync = true,})
    math.randomseed(os.time())
    love.window.setTitle('PONG')

P1score=0
P2score=0

player1 = paddle(10,30,3,20)
player2 = paddle(VIRTUAL_WIDTH-10,VIRTUAL_HEIGHT-30,3,20)

ball = Ball(VIRTUAL_WIDTH/2,VIRTUAL_HEIGHT/2,4,4)

gameState='start'
end


function love.update(dt)
   if love.keyboard.isDown('w')then
    player1.dy= -Paddle_Speed
   elseif love.keyboard.isDown('s')then 
    player1.dy= Paddle_Speed
   else
    player1.dy= 0 
   end

   if love.keyboard.isDown('up')then
    player2.dy= -Paddle_Speed
   elseif love.keyboard.isDown('down')then 
    player2.dy= Paddle_Speed
   else
    player2.dy= 0 
   end

   if gameState=='serve'then
    ball.dy=math.random(-50,50)
    if Servingplayer== 1 then
        ball.dx=math.random(140,200)
    else  
        ball.dx=-math.random(140,200)
    end
   end

    if gameState=='play' then
        if ball:collides(player1) then 
            ball.dx= -ball.dx * 1.0003
            ball.x= player1.x + 3
            if ball.dy < 0 then 
                ball.dy=-math.random(10,150)
            else 
                ball.dy= math.random(10,150)
            end
        end
        if ball:collides(player2) then 
            ball.dx= -ball.dx * 1.5
            ball.x = player2.x-4
            if ball.dy < 0 then 
                ball.dy=-math.random(10,150)
            else 
                ball.dy= math.random(10,150)
            end
        end
        if ball.y<=0 then
            ball.y = 0
            ball.dy=-ball.dy
        end
        if ball.y >= VIRTUAL_HEIGHT-4 then
            ball.y= VIRTUAL_HEIGHT-4
            ball.dy=-ball.dy
        end
        if ball.x < 0 then 
            Servingplayer= 1
            P2score=P2score+1
            gameState='serve'
            ball:reset()
        end
        if ball.x >VIRTUAL_WIDTH+4 then
            Servingplayer=2
            P1score=P1score+1
            gameState='serve'
            ball:reset()
        end



        ball:update(dt)
    end
    player1:update(dt)
    player2:update(dt)


end

function love.keypressed(key)
    if key=='escape' then
        love.event.quit()
    

    elseif key=='enter' or key=='return' then 
        if gameState=='start'then
            gameState='serve'
        elseif gameState=='serve' then 
            gameState='play'
        end
    end    
end

function love.draw()
   push:apply('start')
   love.graphics.clear(40/255,42/255,50/255,255/255)
   if gameState=='start'then
     love.graphics.printf('GAME START!',0,0,VIRTUAL_WIDTH,'center')
   elseif gameState=='serve' then
    if Servingplayer==1 then
        love.graphics.printf('PLAYER1 serve',0,0,VIRTUAL_WIDTH,'center')
    else
        love.graphics.printf('PLAYER2 serve',0,0,VIRTUAL_WIDTH,'center')
    end
    elseif gameState=='play' then
            love.graphics.printf('GAME PLAY!',0,0,VIRTUAL_WIDTH,'center')
   end 
   love.graphics.print(tostring(P1score),VIRTUAL_WIDTH/2-90,0)
   love.graphics.print(tostring(P2score),VIRTUAL_WIDTH/2+90,0)
   player1:render()
   player2:render()
   ball:render()
   
   push:apply('end') 
end

