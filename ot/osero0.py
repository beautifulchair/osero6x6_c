class Board:
	def __init__(self):
		self.board = [0 for _ in range(N**2)]
	def printBoard(self, flag=True):
		if flag:
			with open(filename, "a") as fo:
				for i in self.board:
					print(i, end="", file=fo)
			print()		
		else:
			for i in self.board:
					print(i, end="")
			print()		
	def changeBoard(self, x, y, value):
		self.board[x+y*8] = value
	def getValue(self, x, y):
		return self.board[y*8+x)	
	def getDirectionArray(self, x, y, direction):
		ans = []
		direX = direction[0]
		direY = direction[1]
		c = x
		r = y
		if(direction == [0, 0]):
			return []
		while(0<=r<=6 and 0<=c<=6):
			c+=direX
			r+=direY
			ans.append(self.board[r*8+c])
		return ans
	def ifAviable(self, x, y, colar):
		value = self.getValue(x, y)
		if (value in [1, 2]):
			return False
		for direction in [[1, 1], [1, 0], [1, -1], [0, 1], [0, -1], [-1, 1 ], [-1, 0], [-1, -1]]:
			array = getDirectionArray(self, x, y, direction)
			if (len(array)<2):
				continue
			if (array[0] != 3-colar):
				continue
			i = 0
			for x in array:
				if(x )



if __name__ == "__main__":
	filename = ""
	N = 8
	b1 = Board()
	b1.changeBoard(3, 3, 2)
	b1.changeBoard(3, 4, 1)
	b1.changeBoard(4, 3, 1)
	b1.changeBoard(4, 4, 2)
	b1.printBoard(False)
	print(b1.getDirectionArray(3, 3, [1, 1]))
	
