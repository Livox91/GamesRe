ServeState = Class{__includes =BaseState}

function ServeState:enter(params)
    self.paddle = params.paddle
    self.brick = params.brick
    self.health = params.health
    self.score = params.score

    self.ball = Ball()
    self.ball.skin = math.random(7)
    
end

function ServeState:update(dt)
    self.paddle:update(dt)
    self.ball.x = self.paddle.x + (self.paddle.width/2)-4
    self.ball.y = self.paddle.y -8

    if love.keyboard.wasPressed('enter') or love.keyboard.wasPressed('return') then
        gStateMachine:change('play',{
            paddle = self.paddle,
            brick = self.brick,
            ball = self.ball, 
            health = self.health,
            score = self.score
        })
    end

    if love.keyboard.wasPressed('escape') then
        love.event.quit()
    end

end
function ServeState:render() 
    self.paddle:render()
    self.ball:render()
    for k, brick in pairs(self.brick) do
        brick:render()
    end
    renderScore(self.score)
    renderHealth(self.health)

    love.graphics.setFont(gFonts['medium'])
    love.graphics.printf('Press Enter To Serve', 0 , VIRTUAL_HEIGHT/2,VIRTUAL_WIDTH,'center')

end
