from game import LogicArrows, Arrow, SIZE, ARROW_UP, ARROW_RIGHT, ARROW_LEFT, ARROW_BOTTOM
import pygame

ArrowSize = 35

gameplay = LogicArrows()

pygame.init()
screen = pygame.display.set_mode((ArrowSize * SIZE, ArrowSize * SIZE))
done = False
 
textures = {
    'arrow_1': pygame.image.load('textures/arrow_1.png'),
    'arrow_2': pygame.image.load('textures/arrow_2.png'),
    'arrow_3': pygame.image.load('textures/arrow_3.png'),
}

clock = pygame.time.Clock()

direction = ARROW_UP
selected_arrow = 1

def rotate(image, direction):
    if direction == ARROW_UP:
        return image
    if direction == ARROW_RIGHT:
        return pygame.transform.rotate(image, -90)
    if direction == ARROW_BOTTOM:
        return pygame.transform.rotate(image, -180)
    if direction == ARROW_LEFT:
        return pygame.transform.rotate(image, -270)

while not done:
    screen.fill((255, 255, 255))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos[0] // ArrowSize, event.pos[1] // ArrowSize
            arrow = Arrow()
            if event.button == 1:
                arrow.type = selected_arrow
                arrow.direction = direction
                gameplay.set_arrow(x, y, arrow)
            if event.button == 2:
                arrow.type = 0
                gameplay.set_arrow(x, y, arrow)
            if event.button == 3:
                gameplay.tick()
    pressed = pygame.key.get_pressed()
    if pressed[pygame.K_w]: direction = ARROW_UP
    if pressed[pygame.K_s]: direction = ARROW_BOTTOM
    if pressed[pygame.K_a]: direction = ARROW_LEFT
    if pressed[pygame.K_d]: direction = ARROW_RIGHT
    if pressed[pygame.K_1]: selected_arrow = 1
    if pressed[pygame.K_2]: selected_arrow = 2
    if pressed[pygame.K_3]: selected_arrow = 3
    
    # for y in range(10):
        # for x in range(10):
            # arrow = gameplay.get_arrow(x, y)
            # if (arrow.type > 0 and gameplay.instance[0].power_map[y][x] == 1):
            #     pygame.draw.rect(screen, (255, 0, 0), (ArrowSize * x, ArrowSize * y, ArrowSize, ArrowSize))
            # if (arrow.type > 0 and gameplay.instance[0].power_map[y][x] == 2):
            #     pygame.draw.rect(screen, (255, 0, 255), (ArrowSize * x, ArrowSize * y, ArrowSize, ArrowSize))
            # if arrow.type > 0:
                # screen.blit(rotate(textures['arrow_' + str(arrow.type)], arrow.direction), (ArrowSize * x, ArrowSize * y))
    pygame.display.flip()

gameplay.delete()
