Paddle = Class{}

function Paddle:init()
    self.x = VIRTUAL_WIDTH/2 - 32
    self.y = VIRTUAL_HEIGHT- 32

    self.dx = 0 
    self.width = 64
    self.height = 16
    self.skin = 1 
    self. size = 2

end

function Paddle:update(dt) 
    if love.keyboard.isDown('a') then
        self.dx = -PADDLE_SPEED
    elseif love.keyboard.isDown('d') then
        self.dx = PADDLE_SPEED
    else
        self.dx = 0
    end
    
    if self.dx < 0 then 
        self.x = math.max(0 , self.x + self.dx*dt)
    end
    if self.dx < VIRTUAL_WIDTH then
        self.x = math.min(VIRTUAL_WIDTH-self.width , self.x+self.dx * dt)
    end

end

function Paddle:render()
    love.graphics.draw(gTexture['main'], gFrames['paddles'][self.size + 4 * (self.skin -1)],self.x,self.y)
    
end