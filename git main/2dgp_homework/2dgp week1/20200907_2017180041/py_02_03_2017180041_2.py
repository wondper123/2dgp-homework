import turtle
turtle.reset()

turtle.penup()
x=-250
y=250
turtle.goto(x,y)
count=6
while(count>0):
	if(count<6):
                y=y-100*(6-count)
	turtle.goto(x,y)
	turtle.pendown()
	turtle.forward(500)
	turtle.penup()
	if(count<6):
		x=x+100*(6-count)
		y=y+100*(6-count)
	turtle.goto(x,y)
	turtle.right(90)
	turtle.pendown()
	turtle.forward(500)
	turtle.penup()
	turtle.goto(-250,250)
	x=-250
	y=250
	turtle.left(90)
	count=count-1
turtle.exitonclick()