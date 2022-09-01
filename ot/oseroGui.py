import sys
import tkinter

root = tkinter.Tk()
root.title("osero gui")
root.geometry("500x500")

canvas = tkinter.Canvas(root, width = 400, height = 400)
canvas.place(x = 50, y = 50)
for x in range(8):
	for y in range(8):
		canvas.create_rectangle(50*x, 50*y, 50*(x+1), 50*(y+1), fill = 'green', tag = "board{x}{y}")
		canvas.create_oval(5+50*x, 5+50*y, -5*50*(x+1), -5+50*(y+1), width = 0, tag = "stone{x}{y}")

root.mainloop()
