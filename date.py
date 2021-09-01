import turtle, time

def drawGap(): 
    turtle.penup()
    turtle.fd(5)
def drawLine(draw): 
    drawGap()
    turtle.pendown()if draw else turtle.penup()
    turtle.fd(40)
    drawGap()
def drawDigit(digit): 
    turtle.left (90)
    drawLine(True) if digit in [0,4,5,6,7,8,9] else drawLine(False) 
    turtle.right(90)
    drawLine(True) if digit in [0,2,3,5,6,7,8,9] else drawLine(False) 
    turtle.right(90)
    drawLine(True) if digit in [0,1,2,3,4,7,8,9] else drawLine(False) 
    turtle.right(90)
    drawLine(True) if digit in [2,3,4,5,6,8,9] else drawLine(False)
    turtle.left(90)

    drawLine(True) if digit in [0,2,6,8] else drawLine(False)
    turtle.left(90)
    drawLine(True) if digit in [0,2,3,5,6,8,9] else drawLine(False)
    turtle.left(90)
    drawLine(True) if digit in [0,1,3,4,5,6,7,8,9] else drawLine(False)
    turtle.right(90)
    drawGap()
    drawGap()
    drawGap()
    drawGap()






def drawDate(date): 
    turtle.pencolor("red") 
    for i in date:
        if i == '-':
            turtle.write('Y',font=("Arial", 18, "normal")) 
            turtle.pencolor("green")
            turtle.fd(40)
        elif i == '=':
            turtle.write('M',font=("Arial", 18, "normal"))     
            turtle.pencolor("blue")
            turtle.fd(40)
        elif i == '+':
            turtle.write('D',font=("Arial", 18, "normal"))
        else: 
            drawDigit(eval(i))


def drawTime(time): 
    turtle.pencolor("yellow") 
    for i in time:
        if i == ':':
            drawGap()
            drawGap()
            drawGap()
            drawGap()
            drawGap()
            drawGap()
            drawGap()
        else: 
            drawDigit(eval(i))


def main2():
    turtle.speed(0)
    turtle.setup(800, 400, 0,0) 
    turtle.penup()
    turtle.goto(-300,100)
    turtle.pensize(5)
    drawDate(time.strftime('%Y-%m=%d+',time.gmtime()))
    turtle.penup()
    turtle.goto(-250,-100)
    drawTime(time.strftime("%H:%M:%S"))
    turtle.hideturtle()
    turtle.done()
def main():
    turtle.setup(800, 500, 0,0) 
    turtle.penup()
    turtle.fd(-300) 
    turtle.fd(-300) 
    turtle.pensize(5)
    #for i in range (9):
        
    drawDigit(8)
    turtle.done()
main2()