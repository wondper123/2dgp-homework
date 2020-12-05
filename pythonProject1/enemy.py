from pico2d import *
import gfw
from gobj import *
import life_gauge
import time
import bullet

term = 6

class Enemy:
    SIZE = 31
    init_time = time.time()
    def __init__(self, x, speed, level):
        # self.pos = get_canvas_width() // 2, get_canvas_height() // 2
        self.x, self.y = x, get_canvas_height() + (Enemy.SIZE+(level%3))
        self.dx, self.dy = 0, speed
        self.level = level
        self.max_life = level * 100
        self.life = self.max_life
        self.image = gfw.image.load(RES_DIR + '/enemy_%d.png' % (level))
        self.fidx = 0
        self.HP = level * 10


        self.src_width = self.image.w // term
        self.src_height = self.image.h
        self.time = 0
    def draw(self):
        sx = self.fidx * self.src_width
        self.image.clip_draw(sx, 0, self.src_width, self.src_height, self.x, self.y)
        gy = self.y - Enemy.SIZE // 2
        rate = self.life / self.max_life
        life_gauge.draw(self.x, gy, Enemy.SIZE - 10, rate)

    def update(self):
        self.time += gfw.delta_time
        self.fidx = int(self.time * 10 + 0.5) %term
        # self.x += self.dx
        self.y += self.dy * gfw.delta_time

        if self.y < -Enemy.SIZE:
            self.remove()

        if self.time%10>4 and self.time%10<4.1:
            self.fire()
            print("적 총알 발사됨!!")

    def fire(self):
        enemybullet = bullet.EnemyBullet(self.x, self.y + 28, 400)
        gfw.world.add(gfw.layer.enemybullet, enemybullet)

    def remove(self):
        gfw.world.remove(self)

    def decrease_life(self, amount):
        self.life -= amount
        return self.life <= 0

    def score(self):
        return self.max_life

    def get_bb(self):
        half = Enemy.SIZE // 2 - 5
        return self.x - half, self.y - half, self.x + half, self.y + half
