Pipe=Class{}

local PIPE_IMAGE=love.graphics.newImage('images/pipe.png')
PIPE_SPEED=60
PIPE_WIDTH=70
PIPE_HEIGHT=430

function Pipe:init(oreintation,y)
    self.x=VIRTUAL_WIDTH
    self.y= y
    self.width= PIPE_IMAGE:getWidth()
    self.height=PIPE_HEIGHT
    self.oreintation=oreintation
    
end

function Pipe:update(dt)
    
end

function Pipe:render()
    love.graphics.draw(PIPE_IMAGE,self.x,
    (self.oreintation=='top'and self.y + PIPE_HEIGHT or self.y ),0,1,
    self.oreintation=='top' and -1 or 1 )
end