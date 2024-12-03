GameoverState = Class{__includes =BaseState}

function  GameoverState:enter(params)
    self.score = params.score
    
end

function GameoverState:update(dt)
    if love.keyboard.wasPressed('enter') or love.keyboard.wasPressed('return') then
        gStateMachine:change('start')
    end
    
    if love.keyboard.wasPressed('escape') then
        love.event.quit()
    end
end
function GameoverState:render()
    love.graphics.setFont(gFonts['large'])
    love.graphics.printf('Game Over', 0 ,VIRTUAL_HEIGHT/3,VIRTUAL_WIDTH,'center')
    love.graphics.setFont(gFonts['medium'])
    love.graphics.printf('Final Score: '.. tostring(self.score),0 ,VIRTUAL_HEIGHT/2,VIRTUAL_WIDTH,'center')
    love.graphics.printf('Press ENTER',0,VIRTUAL_HEIGHT-VIRTUAL_HEIGHT/4,VIRTUAL_WIDTH,'center')
    
end