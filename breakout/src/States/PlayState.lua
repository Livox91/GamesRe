PlayState = Class{__includes = BaseState}

function PlayState:enter(params)
    self.paddle = params.paddle
    self.ball = params.ball
    self.brick = params.brick
    self.health = params.health
    self.score = params.score

    self.ball.dx = math.random(-200,200)
    self.ball.dy = math.random (-60, -90) 
end

function PlayState:update(dt)

    if self.paused then    
        if love.keyboard.wasPressed('space') then
            self.paused = false
            gSounds['pause']:play()
        else
            return
        end 
    elseif love.keyboard.wasPressed('space') then 
        self.paused = true
        gSounds['pause']:play()
    end


    self.paddle:update(dt)
    self.ball:update(dt)

    if self.ball:collides(self.paddle) then
        
        self.ball.y = self.paddle.y - 8 
        self.ball.dy = -self.ball.dy


        if self.ball.x < self.paddle.x + (self.paddle.width/2) and self.paddle.dx < 0 then
            self.ball.dx = -50 + -(8*(self.paddle.x+self.paddle.width/2-self.ball.x))
        elseif self.ball.x > self.paddle.x + (self.paddle.width/2) and self.paddle.dx> 0 then
            self.ball.dx = 50 + (8* math.abs(self.paddle.x+self.paddle.width/2-self.ball.x)) 
        end

        gSounds['paddle-hit']:play()
    end
    
    for k , brick in pairs(self.brick)  do 
        
        if brick.inplay and self.ball:collides(brick) then
            brick:hit()

            self.score = self.score + (brick.tier * 200 + brick.color * 25 )

            if self.ball.x +2 <brick.x and self.ball.dx > 0 then
                self.ball.dx = -self.ball.dx
                self.ball.x = brick.x - 8
            elseif self.ball.x -6 > brick.x + brick.width and self.ball.dx < 0 then
                self.ball.dx = -self.ball.dx
                self.ball.x = brick.x+32
            elseif self.ball.y < brick.y then
                self.ball.y = brick.y-8
                self.ball.dy = -self.ball.dy
            else
                self.ball.dy = -self.ball.dy
                self.ball.y = brick.y+16
            end

            self.ball.dy = self.ball.dy * 1.02

            break

        end
    end

    if self.ball.y >= VIRTUAL_HEIGHT then 
        self.health = self.health -1
        gSounds['hurt']:play()

        if self.health == 0 then
            gStateMachine:change('gameover',{
                score = self.score
            })
        else
            gStateMachine:change('serve' , {
                paddle = self.paddle,
                brick= self.brick,
                health = self.health,
                score = self.score ,

            })
        end
    end


    if love.keyboard.wasPressed('escape') then
        love.event.quit()
    end
end

function PlayState:render()

    for k , brick in pairs(self.brick)  do
        brick:render()
    end

    for k, brick in pairs(self.brick) do
        brick:renderParticles()
    end

    self.paddle:render()
    renderScore(self.score)
    self.ball:render()

    if self.paused == true then 
        love.graphics.setFont(gFonts['large'])
        love.graphics.printf("Paused", 0 ,VIRTUAL_HEIGHT/2-16,VIRTUAL_WIDTH,'center')
    end
        
end

