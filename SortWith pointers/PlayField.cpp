#include "PlayField.h"

PlayField::CellState PlayField::operator[](CellIdx idx)
{
	return state[GetLinearIdxFromCell(idx)];
}

std::vector<PlayField::CellIdx*> PlayField::GetEmptyCells()
{
	std::vector<CellIdx*> emptyCells;
	for (int i = 0; i < 9; i++)
		if (state[i] == csEmpty) emptyCells.push_back(&GetCellIdxFromLinear(i));
	return emptyCells;
}

PlayField::FieldStatus PlayField::checkFieldStatus()
{
	int linesToCheck[8][3] = { {0, 1, 2},//horizontal
							   {3, 4, 5}, 
							   {6, 7, 8}, 
							   {0, 3, 6},//vertical
							   {1, 4, 7},
							   {2, 5, 8},
							   {0, 4, 8},//diagonal
							   {2, 4, 6}
							 };

	int crosses = 0, noughts = 0;
	FieldStatus fieldStatus;
	bool canMove = !GetEmptyCells().empty();
	for (int i = 0; i < 8; i++)
	{
		CellState st = CheckForWin(linesToCheck[i]);
		if (st == csNought)	 return fsNoughtsWin;
		else if (st == csCross)	return fsCrossesWin;
	}

	for (auto cell : state)	{
		if (cell == csCross) crosses++;
		else if (cell == csNought) noughts++;
	}
	
	return abs(crosses - noughts) < 2 ? canMove ? fsNormal : fsDraw : fsInvalid;
}

PlayField PlayField::makeMove(CellIdx idx) const {
	assert(state[GetLinearIdxFromCell(idx)] == csEmpty);
	PlayField changedField = PlayField(*this);
	changedField.state[GetLinearIdxFromCell(idx)] = IdentifyWhoseMove();
	return changedField;
}

PlayField PlayField::operator+(CellIdx idx) {
	assert(state[GetLinearIdxFromCell(idx)] == csEmpty);
	state[GetLinearIdxFromCell(idx)] = IdentifyWhoseMove();
	return *this;
}

int PlayField::GetLinearIdxFromCell(CellIdx idx) const {
	return idx.GetX() + idx.GetY() * 3;
}

PlayField::CellIdx PlayField::GetCellIdxFromLinear(int idx) const {
	return PlayField::CellIdx::CreateCell(idx / 3, idx % 3);
}

PlayField::CellState PlayField::IdentifyWhoseMove() const {
	int crosses = 0, noughts = 0;
	for (auto cell : state)	{
		if (cell == csCross) crosses++;
		else if (cell == csNought) noughts++;
	}
	return (crosses - noughts) >= 1 ? csNought : csCross;
}

PlayField::CellState PlayField::CheckForWin(int* line) const {
	return (state[*line] == state[*(line + 1)]) && (state[*line] == state[*(line + 2)]) && (state[*line] == csCross) ? csCross
		: (state[*line] == state[*(line + 1)]) && (state[*line] == state[*(line + 2)]) && (state[*line] == csNought) ? csNought
		: csEmpty;
}
