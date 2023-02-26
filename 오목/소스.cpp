#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define BOARD_SIZE 19
/*2020112027 박상욱*/

class Game_Board	//바둑판에 관련된 클래스
{
private:
	int inputrow;	//입력받는 행의 값
	int inputcol;	//입력받는 열의 값
public:
	string gameBoard[BOARD_SIZE][BOARD_SIZE];	//게임판에 흰돌과 검은돌을 표시해주는 배열
	int weight[BOARD_SIZE][BOARD_SIZE];			//게임판의 각 칸에 가중치를 할당하는 배열
	int saveweight[100];						//둘 수 있는 위치들을 저장하는 배열
	
	Game_Board();			//바둑판의 모든 점들을 +로 초기화

	void printGB();			//현재 바둑판에 돌들이 놓여있는 상황을 출력하는 함수
	int player_chakshu();	//사용자의 차례에 놀 흑돌의 좌표를 입력받는 함수
	void weighting();		//돌들이 현재 놓여있는 상황을 보고 흑돌 주변 8점에 +2, 백돌 주변 8점에 -2를 하는 함수
	void printw();			//돌들이 놓여 있는 상황의 가중치를 가시적으로 표시해주는 함수
	void resetw();			//모든 가중치를 0으로 초기화하는 함수
	void resets();			//모든 saveweight[]를 초기화하는 배열
	int cpu_chakshu_weight();	//가중치를 이용하여 컴퓨터가 착수한다.
	int cpu_chackshu_def3s();	//사용자의 돌이 3개의 돌이 나란히 있을 때 컴퓨터가 방어한다.
	int cpu_chackshu_def4s();	//사용자의 돌이 4개의 돌이 나란히 있을 때 컴퓨터가 방어한다.
	int cpu_chackshu_def1_2s();	//사용자의 돌이 1 띄고 2개의 돌이 나란히 있을 때 컴퓨터가 방어한다.
	int cpu_chackshu_def1_3s();	//사용자의 돌이 1 띄고 3개의 돌이 나란히 있을 때 컴퓨터가 방어한다.
	int cpu_chackshu_def2_2s();	//사용자의 돌이 2 띄고 2개의 돌이 나란히 있을 때 컴퓨터가 방어한다.
	int cpu_chackshu_atk2s();	//나란한 2개의 컴퓨터의 돌의 양 쪽 끝에 사용자의 돌이 없고, 방어할 필요가 없을 경우, 공격한다.
	int cpu_chackshu_atk3s();	//나란한 3개의 컴퓨터의 돌이 있고, 방어할 필요가 없을 경우, 공격한다.
	int cpu_chackshu_atk4s();	//나란한 4개의 컴퓨터의 돌이 있을 경우 공격한다.
	int cpu_chackshu_atk1_2s();	//나란한 1 띄고 2개의 컴퓨터의 돌이 있고, 방어할 필요가 없을 경우, 공격한다.
	int cpu_chackshu_atk1_3s();	//나란한 1 띄고 3개의 컴퓨터의 돌이 있을 경우 공격한다.
	int cpu_chackshu_atk2_2s();	//나란한 2 띄고 2개의 컴퓨터의 돌이 있을 경우 공격한다.
	int cpu_chackshu_atk1_1s();	//나란한 1 띄고 1개의 컴퓨터의 돌이 있고, 방어할 필요가 없을 경우, 공격한다.
	int count_cpustone();		//게임판에서 현재 컴퓨터의 돌의 개수를 세는 함수.
	bool win_player();		//사용자의 돌이 5개가 나란히 있으면 승리한다.
	bool win_cpu();			//컴퓨터의 돌이 5개가 나란히 있으면 승리한다.
};

Game_Board::Game_Board()	//gameBoard 배열을 +로 초기화
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			gameBoard[i][j] = "+";
			weight[i][j] = 0;
		}
	}
}

void Game_Board::printGB()	//바둑판 출력
{
	cout << endl << "      ";
	for (int i = 0; i < BOARD_SIZE; i++)	//가로 좌표 출력
	{
		if (i < 10)		//가로 좌표가 10보다 작을 경우 0을 붙인다.
			cout << " 0" << i;
		else			//가로 좌표가 10이상일 경우 그냥 출력한다.
			cout << " " << i;
	}
	cout << endl;

	if (BOARD_SIZE % 2 == 0)	//BOARD_SIZE가 짝수라면
	{
		cout << "ㅡㅡㅡ";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
			cout << "ㅡㅡㅡ";
	}
	else						//BOARD_SIZE가 홀수라면
	{
		cout << "ㅡㅡㅡㅡㅡ";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
		{
			cout << "ㅡㅡㅡ";
		}
	}
	cout << endl;
	
	for (int i = 0; i < BOARD_SIZE; i++)	//세로 좌표 출력
	{
		if (i < 10)		//세로 좌표가 10보다 작을 경우 0을 붙인다.
			cout << " 0" << i << " | ";
		else			//세로 좌표가 10이상일 경우 그냥 출력한다.
			cout << " " << i << " | ";

		for (int j = 0; j < BOARD_SIZE; j++)	//흑돌, 백돌 출력
		{
			if (gameBoard[i][j] == "●" || gameBoard[i][j] == "○")
				cout << " " << gameBoard[i][j];
			else
				cout << "  " << gameBoard[i][j];
		}

		cout << endl;
	}
}

int Game_Board::player_chakshu()
{
	while (true)
	{
		cout << endl;
		cout << "당신의 차례입니다." << endl;
		cout << "착수할 위치를 선택하세요." << endl;
		cin >> inputrow >> inputcol;	//착수할 위치(가로, 세로)를 입력받는다.

		if (gameBoard[inputcol][inputrow] == "●" || gameBoard[inputcol][inputrow] == "○")	//돌이 있는 자리에는 착수할 수 없다.
		{
			cout << "그 곳엔 돌이 있어 착수할 수 없습니다." << endl;
			continue;
		}

		else if (inputcol >= 19 || inputcol < 0 || inputrow >= 19 || inputcol < 0)	//게임판의 밖에는 착수할 수 없다.
		{
			cout << "그 곳은 게임판의 밖입니다." << endl;
			continue;
		}

		else
		{
			break;
		}
	}

	gameBoard[inputcol][inputrow] = "●";	//입력받은 위치에 착수한다.
	return 0;
}

void Game_Board::weighting()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●")	//사용자가 착수한 점을 둘러싸고 있는 8점에 +2의 가중치
			{
				weight[i - 1][j - 1] += 2;
				weight[i - 1][j] += 2;
				weight[i - 1][j + 1] += 2;
				weight[i][j - 1] += 2;
				weight[i][j + 1] += 2;
				weight[i + 1][j - 1] += 2;
				weight[i + 1][j] += 2;
				weight[i + 1][j + 1] += 2;
			}
			
			else if (gameBoard[i][j] == "○")	//컴퓨터가 착수한 점을 둘러싸고 있는 8점에 -2의 가중치
			{
				weight[i - 1][j - 1] -= 2;
				weight[i - 1][j] -= 2;
				weight[i - 1][j + 1] -= 2;
				weight[i][j - 1] -= 2;
				weight[i][j + 1] -= 2;
				weight[i + 1][j - 1] -= 2;
				weight[i + 1][j] -= 2;
				weight[i + 1][j + 1] -= 2;
			}
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)	//돌이 이미 있는 자리의 가중치를 -99로 만든다.
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●" || gameBoard[i][j] == "○")
			{
				weight[i][j] = -99;
			}
		}
	}
}

void Game_Board::printw()	//가중치를 가시적으로 출력
{
	cout << endl << "      ";
	for (int i = 0; i < BOARD_SIZE; i++)	//가로 좌표 출력
	{
		if (i < 10)
			cout << " 0" << i;
		else
			cout << " " << i;
	}
	cout << endl;

	if (BOARD_SIZE % 2 == 0)
	{
		cout << "ㅡㅡㅡ";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
			cout << "ㅡㅡㅡ";
	}
	else
	{
		cout << "ㅡㅡㅡㅡㅡ";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
		{
			cout << "ㅡㅡㅡ";
		}
	}
	cout << endl;

	for (int i = 0; i < BOARD_SIZE; i++)	//세로 좌표 출력
	{
		if (i < 10)
			cout << " 0" << i << " | ";
		else
			cout << " " << i << " | ";

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (weight[i][j] > 0)		//가중치가 양수일 경우의 가중치 출력
				cout << " +" << weight[i][j];

			else if (weight[i][j] == 0)	//가중치가 0일 경우의 가중치 출력
				cout << "  " << weight[i][j];

			else if (weight[i][j] < 0)	//가중치가 음수일 경우의 가중치 출력
				cout << " " << weight[i][j];
		}

		cout << endl;
	}
}

void Game_Board::resetw()	//모든 가중치를 0으로 초기화
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			weight[i][j] = 0;
		}
	}
}

void Game_Board::resets()	//모든 saveweight[]를 초기화
{
	for (int i = 0; i < 100; i++)
		saveweight[i] = 0;
}

int Game_Board::cpu_chakshu_weight()
{
	int max = weight[0][0];	//초기의 max값을 weight[0][0]으로 설정
	int count = 0;			//weight값들 중 가장 큰 값의 개수

	
	for (int i = 0; i < BOARD_SIZE; i++)	//모든 weight를 비교해서 가장 큰 weight값 찾기
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			if (max < weight[i][j + 1])
				max = weight[i][j + 1];
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)	//가장 큰 weight값과 같은 weight값들을 찾기
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			if (max == weight[i][j])
			{
				saveweight[count] = 100 * i + j;	//saveweight 배열에 i와 j값을 십의 자리까지는 j, 백의 자리부터는 i의 형식으로 저장한다.
				count++;	//count값을 1 증가시킨다.
			}
		}
	}

	srand(time(NULL));
	int random = rand() % count;	//0부터 count-1까지의 수들 중 하나를 무작위로 뽑는다.

	int b = saveweight[random] % 100;			//무작위로 뽑힌 j를 구하고 b에 대입한다.
	int a = (saveweight[random] - b) / 100;		//무작위로 뽑힌 i를 구하고 a에 대입한다.

	gameBoard[a][b] = "○";		//○돌로 컴퓨터가 착수한다.
	return 0;
}

int Game_Board::cpu_chackshu_def3s()
{
	//가로로 3개일 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "●" && gameBoard[i][j + 2] == "●")
			{
				//만약 3개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있다면 굳이 막을 필요가 없다.
				if (j - 1 == -1 || j + 3 == BOARD_SIZE) {}

				//만약 3개의 돌의 끝 중 한 쪽 끝이 이미 컴퓨터의 돌로 막혀 있다면 굳이 막을 필요가 없다.
				else if (gameBoard[i][j - 1] == "○" || gameBoard[i][j + 3] == "○") {}

				//4개의 돌은 검색하지 않는다.
				else if (gameBoard[i][j - 1] == "●" || gameBoard[i][j + 3] == "●") {}

				//막혀 있지 않을 경우 두 끝 중 한 쪽에 무작위로 착수한다.
				else
				{
					saveweight[0] = 100 * i + j - 1;
					saveweight[1] = 100 * i + j + 3;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[a][b] = "○";
					}
					return 0;
				}
			}
		}
	}

	//세로로 3개일 경우
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "●" && gameBoard[i + 2][j] == "●")
			{
				//만약 3개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있다면 굳이 막을 필요가 없다.
				if (i - 1 == -1 || i + 3 == BOARD_SIZE) {}

				//만약 3개의 돌의 끝 중 한 쪽 끝이 이미 컴퓨터의 돌로 막혀 있다면 굳이 막을 필요가 없다.
				else if (gameBoard[i - 1][j] == "○" || gameBoard[i + 3][j] == "○") {}

				//4개의 돌은 검색하지 않는다.
				else if (gameBoard[i - 1][j] == "●" || gameBoard[i + 3][j] == "●") {}

				//막혀 있지 않을 경우 두 끝 중 한 쪽에 무작위로 착수한다.
				else
				{
					saveweight[0] = 100 * (i - 1) + j;
					saveweight[1] = 100 * (i + 3) + j;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[a][b] = "○";
					}
					return 0;
				}
			}
		}
	}

	//오른쪽 아래 대각선으로 3개일 경우
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "●" && gameBoard[i + 2][j + 2] == "●")
			{
				//만약 3개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있다면 굳이 막을 필요가 없다.
				if (i - 1 == -1 || j - 1 == -1 || i + 3 == BOARD_SIZE || j + 3 == BOARD_SIZE) {}

				//만약 3개의 돌의 끝 중 한 쪽 끝이 이미 컴퓨터의 돌로 막혀 있다면 굳이 막을 필요가 없다.
				else if (gameBoard[i - 1][j - 1] == "○" || gameBoard[i + 3][j + 3] == "○") {}

				//4개의 돌은 검색하지 않는다.
				else if (gameBoard[i - 1][j - 1] == "●" || gameBoard[i + 3][j + 3] == "●") {}

				//막혀 있지 않을 경우 두 끝 중 한 쪽에 무작위로 착수한다.
				else
				{
					saveweight[0] = 100 * (i - 1) + j - 1;
					saveweight[1] = 100 * (i + 3) + j + 3;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[a][b] = "○";
					}
					return 0;
				}
			}
		}
	}

	//오른쪽 위 대각선으로 3개일 경우
	for (int i = 2; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "●" && gameBoard[i - 2][j + 2] == "●")
			{
				//만약 3개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있다면 굳이 막을 필요가 없다.
				if (i + 1 == BOARD_SIZE || j - 1 == -1 || i - 3 == -1 || j + 3 == BOARD_SIZE) {}

				//만약 3개의 돌의 끝 중 한 쪽 끝이 이미 컴퓨터의 돌로 막혀 있다면 굳이 막을 필요가 없다.
				else if (gameBoard[i + 1][j - 1] == "○" || gameBoard[i - 3][j + 3] == "○") {}
				
				//4개의 돌은 검색하지 않는다.
				else if (gameBoard[i + 1][j - 1] == "●" || gameBoard[i - 3][j + 3] == "●") {}

				//막혀 있지 않을 경우 두 끝 중 한 쪽에 무작위로 착수한다.
				else
				{
					saveweight[0] = 100 * (i + 1) + j - 1;
					saveweight[1] = 100 * (i - 3) + j + 3;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[a][b] = "○";
					}
					return 0;
				}
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_def4s()
{
	//가로로 4개일 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "●" && gameBoard[i][j + 2] == "●" && gameBoard[i][j + 3] == "●")
			{
				//4개의 돌의 한 쪽 끝이 벽에 막혀 있다면 다른 한 쪽만 막으면 된다.
				if (j - 1 == -1)
				{
					if (gameBoard[i][j + 4] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i][j + 4] = "○";
						return 0;
					}
				}
				else if (j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i][j - 1] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i][j - 1] = "○";
						return 0;
					}
				}

				//4개의 돌의 한 쪽 끝이 컴퓨터의 돌로 막혀 있다면 다른 한 쪽만 막으면 된다.
				else if (gameBoard[i][j - 1] == "○")
				{
					if (gameBoard[i][j + 4] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i][j + 4] = "○";
						return 0;
					}
				}
				else if (gameBoard[i][j + 4] == "○")
				{
					if (gameBoard[i][j - 1] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i][j - 1] = "○";
						return 0;
					}
				}

				else {}
			}
		}
	}

	//세로로 4개일 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "●" && gameBoard[i + 2][j] == "●" && gameBoard[i + 3][j] == "●")
			{
				//4개의 돌의 한 쪽 끝이 벽에 막혀 있다면 다른 한 쪽만 막으면 된다.
				if (i - 1 == -1)
				{
					if (gameBoard[i + 4][j] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i + 4][j] = "○";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i - 1][j] = "○";
						return 0;
					}
				}

				//4개의 돌의 한 쪽 끝이 컴퓨터의 돌로 막혀 있다면 다른 한 쪽만 막으면 된다.
				else if (gameBoard[i - 1][j] == "○")
				{
					if (gameBoard[i + 4][j] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i + 4][j] = "○";
						return 0;
					}
				}
				else if (gameBoard[i + 4][j] == "○")
				{
					if (gameBoard[i - 1][j] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i - 1][j] = "○";
						return 0;
					}
				}

				else {}
			}
		}
	}

	//오른쪽 아래 대각선으로 4개일 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "●" && gameBoard[i + 2][j + 2] == "●" && gameBoard[i + 3][j + 3] == "●")
			{
				//4개의 돌의 한 쪽 끝이 벽에 막혀 있다면 다른 한 쪽만 막으면 된다.
				if (i - 1 == -1 || j - 1 == -1)
				{
					if (gameBoard[i + 4][j + 4] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i + 4][j + 4] = "○";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j - 1] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i - 1][j - 1] = "○";
						return 0;
					}
				}

				//4개의 돌의 한 쪽 끝이 컴퓨터의 돌로 막혀 있다면 다른 한 쪽만 막으면 된다.
				else if (gameBoard[i - 1][j - 1] == "○")
				{
					if (gameBoard[i + 4][j + 4] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i + 4][j + 4] = "○";
						return 0;
					}
				}
				else if (gameBoard[i + 4][j + 4] == "○")
				{
					if (gameBoard[i - 1][j - 1] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i - 1][j - 1] = "○";
						return 0;
					}
				}

				else {}
			}
		}
	}

	//오른쪽 위 대각선으로 4개일 경우
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "●" && gameBoard[i - 2][j + 2] == "●" && gameBoard[i - 3][j + 3] == "●")
			{
				//만약 4개의 돌의 한 쪽 끝이 벽에 막혀 있다면 다른 한 쪽만 막으면 된다.
				if (i + 1 == BOARD_SIZE || j - 1 == -1)
				{
					if (gameBoard[i - 4][j + 4] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i - 4][j + 4] = "○";
						return 0;
					}
				}
				else if (i - 4 == -1 || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i + 1][j - 1] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i + 1][j - 1] = "○";
						return 0;
					}
				}

				//4개의 돌의 한 쪽 끝이 컴퓨터의 돌로 막혀 있다면 다른 한 쪽만 막으면 된다.
				else if (gameBoard[i + 1][j - 1] == "○")
				{
					if (gameBoard[i - 4][j + 4] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i - 4][j + 4] = "○";
						return 0;
					}
				}

				else if (gameBoard[i - 4][j + 4] == "○")
				{
					if (gameBoard[i + 1][j - 1] == "+")	//놓을 자리가 비어 있다면 착수한다.
					{
						gameBoard[i + 1][j - 1] = "○";
						return 0;
					}
				}

				else {}
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_def1_2s()
{
	//가로로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "●" && gameBoard[i][j + 3] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i][j - 1] == "○" || gameBoard[i][j + 4] == "○") {}

				else
				{
					gameBoard[i][j + 1] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "●" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i][j - 1] == "○" || gameBoard[i][j + 4] == "○") {}

				else
				{
					gameBoard[i][j + 2] = "○";
					return 0;
				}
			}

			else {}
		}
	}

	//세로로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "●" && gameBoard[i + 3][j] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i + 1][j] == "○" || gameBoard[i + 4][j] == "○") {}

				else
				{
					gameBoard[i + 1][j] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "●" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i + 1][j] == "○" || gameBoard[i + 4][j] == "○") {}
				
				else
				{
					gameBoard[i + 2][j] = "○";
					return 0;
				}
			}

			else {}
		}
	}

	//오른쪽 아래 대각선으로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "●" && gameBoard[i + 3][j + 3] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i - 1][j - 1] == "○" || gameBoard[i + 4][j + 4] == "○") {}

				else
				{
					gameBoard[i + 1][j + 1] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "●" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i - 1][j - 1] == "○" || gameBoard[i + 4][j + 4] == "○") {}

				else
				{
					gameBoard[i + 2][j + 2] = "○";
					return 0;
				}
			}

			else {}
		}
	}

	//오른쪽 위 대각선으로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "●" && gameBoard[i - 3][j + 3] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i + 1][j - 1] == "○" || gameBoard[i - 4][j + 4] == "○") {}

				else
				{
					gameBoard[i - 1][j + 1] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "●" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "●")
			{
				//만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
				if (gameBoard[i + 1][j - 1] == "○" || gameBoard[i - 4][j + 4] == "○") {}

				else
				{
					gameBoard[i - 2][j + 2] = "○";
					return 0;
				}
			}

			else {}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_def1_3s()
{
	//가로로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "●" && gameBoard[i][j + 3] == "●" && gameBoard[i][j + 4] == "●")
			{
					gameBoard[i][j + 1] = "○";
					return 0;
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "●" && gameBoard[i][j + 2] == "●" && gameBoard[i][j + 3] == "+" && gameBoard[i][j + 4] == "●")
			{

				gameBoard[i][j + 3] = "○";
				return 0;
			}
		}
	}

	//세로로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "●" && gameBoard[i + 3][j] == "●" && gameBoard[i + 4][j] == "●")
			{
				gameBoard[i + 1][j] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "●" && gameBoard[i + 2][j] == "●" && gameBoard[i + 3][j] == "+" && gameBoard[i + 4][j] == "●")
			{
				gameBoard[i + 3][j] = "○";
				return 0;
			}
		}
	}

	//오른쪽 아래 대각선으로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "●" && gameBoard[i + 3][j + 3] == "●" && gameBoard[i + 4][j + 4] == "●")
			{
				gameBoard[i + 1][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "●" && gameBoard[i + 2][j + 2] == "●" && gameBoard[i + 3][j + 3] == "+" && gameBoard[i + 4][j + 4] == "●")
			{
				gameBoard[i + 3][j + 3] = "○";
				return 0;
			}
		}
	}

	//오른쪽 위 대각선으로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "●" && gameBoard[i - 3][j + 3] == "●" && gameBoard[i - 4][j + 4] == "●")
			{
				gameBoard[i - 1][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "●" && gameBoard[i - 2][j + 2] == "●" && gameBoard[i - 3][j + 3] == "+" && gameBoard[i - 4][j + 4] == "●")
			{
				gameBoard[i - 3][j + 3] = "○";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_def2_2s()
{
	//가로로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "●" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "●" && gameBoard[i][j + 4] == "●")
			{
				gameBoard[i][j + 2] = "○";
				return 0;
			}
		}
	}

	//세로로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "●" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "●" && gameBoard[i + 4][j] == "●")
			{
				gameBoard[i + 2][j] = "○";
				return 0;
			}
		}
	}

	//오른쪽 아래 대각선으로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "●" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "●" && gameBoard[i + 4][j + 4] == "●")
			{
				gameBoard[i + 2][j + 2] = "○";
				return 0;
			}
		}
	}

	//오른쪽 위 대각선으로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "●" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "●" && gameBoard[i - 4][j + 4] == "●")
			{
				gameBoard[i - 2][j + 2] = "○";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk2s()
{
	//가로로 2개일 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			//막혀 있지 않을 경우
			if (gameBoard[i][j - 1] == "+" && gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○" && gameBoard[i][j + 2] == "+")
			{
				//[i][j - 1]의 가중치가 더 클 경우
				if (weight[i][j - 1] > weight[i][j + 2])
				{
					gameBoard[i][j - 1] = "○";
					return 0;
				}

				//[i][j + 2]의 가중치가 더 클 경우
				else if (weight[i][j - 1] < weight[i][j + 2])
				{
					gameBoard[i][j + 2] = "○";
					return 0;
				}

				//두 가중치가 같을 경우
				else
				{
					saveweight[0] = 100 * i + j - 1;
					saveweight[1] = 100 * i + j + 2;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○")
			{
				//한 쪽 끝이 열려 있어야 함
				if (gameBoard[i][j - 1] == "+" || gameBoard[i][j + 2] == "+")
				{
					//만약 2개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
					if (j - 1 == -1)
					{
						if (gameBoard[i][j + 2] == "●") {}

						else
						{
							gameBoard[i][j + 2] = "○";
							return 0;
						}
					}
					else if (j + 2 == BOARD_SIZE)
					{
						if (gameBoard[i][j - 1] == "●") {}

						else
						{
							gameBoard[i][j - 1] = "○";
							return 0;
						}
					}

					//만약 2개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
					else if (gameBoard[i][j - 1] == "●")
					{
						gameBoard[i][j + 2] = "○";
						return 0;
					}
					else if (gameBoard[i][j + 2] == "●")
					{
						gameBoard[i][j - 1] = "○";
						return 0;

					}
				}
			}
		}
	}

	//세로로 2개일 경우
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//막혀 있지 않을 경우
			if (gameBoard[i - 1][j] == "+" && gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○" && gameBoard[i + 2][j] == "+")
			{
				//[i - 1][j]의 가중치가 더 클 경우
				if (weight[i - 1][j] > weight[i + 2][j])
				{
					gameBoard[i - 1][j] = "○";
					return 0;
				}

				//[i + 2][j]의 가중치가 더 클 경우
				else if (weight[i - 1][j] < weight[i + 2][j])
				{
					gameBoard[i + 2][j] = "○";
					return 0;
				}

				//두 가중치가 같을 경우
				else
				{
					saveweight[0] = 100 * (i - 1) + j;
					saveweight[1] = 100 * (i + 2) + j;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○")
			{
				//한 쪽 끝이 열려 있어야 함
				if (gameBoard[i - 1][j] == "+" || gameBoard[i + 2][j] == "+")
				{
					//만약 2개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
					if (i - 1 == -1)
					{
						if (gameBoard[i + 2][j] == "●") {}

						else
						{
							gameBoard[i + 2][j] = "○";
							return 0;
						}
					}
					else if (i + 2 == BOARD_SIZE)
					{
						if (gameBoard[i - 1][j] == "●") {}

						else
						{
							gameBoard[i - 1][j] = "○";
							return 0;
						}
					}

					//만약 2개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
					else if (gameBoard[i - 1][j] == "●")
					{
						gameBoard[i + 2][j] = "○";
						return 0;
					}
					else if (gameBoard[i + 2][j] == "●")
					{
						gameBoard[i - 1][j] = "○";
						return 0;
					}
				}
			}
		}
	}

	//대각선 아래로 2개일 경우
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			//막혀 있지 않을 경우
			if (gameBoard[i - 1][j - 1] == "+" && gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○" && gameBoard[i + 2][j + 2] == "+")
			{
				//[i - 1][j - 1]의 가중치가 더 클 경우
				if (weight[i - 1][j - 1] > weight[i + 2][j + 2])
				{
					gameBoard[i - 1][j - 1] = "○";
					return 0;
				}

				//[i + 2][j + 2]의 가중치가 더 클 경우
				else if (weight[i - 1][j - 1] < weight[i + 2][j + 2])
				{
					gameBoard[i + 2][j + 2] = "○";
					return 0;
				}

				//두 가중치가 같을 경우
				else
				{
					saveweight[0] = 100 * (i - 1) + j - 1;
					saveweight[1] = 100 * (i + 2) + j + 2;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○")
			{
				//한 쪽 끝이 열려 있어야 함
				if (gameBoard[i - 1][j - 1] == "+" || gameBoard[i + 2][j + 2] == "+")
				{
					//만약 2개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
					if (i - 1 == -1 || j - 1 == -1)
					{
						if (gameBoard[i + 2][j + 2] == "●") {}

						else
						{
							gameBoard[i + 2][j + 2] = "○";
							return 0;
						}
					}
					else if (i + 2 == BOARD_SIZE || j + 2 == BOARD_SIZE)
					{
						if (gameBoard[i - 1][j - 1] == "●") {}

						else
						{
							gameBoard[i - 1][j - 1] = "○";
							return 0;
						}
					}

					//만약 2개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
					else if (gameBoard[i - 1][j - 1] == "●")
					{
						gameBoard[i + 2][j + 2] = "○";
						return 0;
					}
					else if (gameBoard[i + 2][j + 2] == "●")
					{
						gameBoard[i - 1][j - 1] = "○";
						return 0;
					}
				}
			}
		}
	}

	//대각선 위로 2개일 경우
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			//막혀 있지 않을 경우
			if (gameBoard[i + 1][j - 1] == "+" && gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○" && gameBoard[i - 2][j + 2] == "+")
			{
				//[i + 1][j - 1]의 가중치가 더 클 경우
				if (weight[i + 1][j - 1] > weight[i - 2][j + 2])
				{
					gameBoard[i + 1][j - 1] = "○";
					return 0;
				}

				//[i - 2][j + 2]의 가중치가 더 클 경우
				else if (weight[i + 1][j - 1] < weight[i - 2][j + 2])
				{
					gameBoard[i - 2][j + 2] = "○";
					return 0;
				}

				//두 가중치가 같을 경우
				else
				{
					saveweight[0] = 100 * (i + 1) + j - 1;
					saveweight[1] = 100 * (i - 2) + j + 2;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○")
			{
				//한 쪽 끝이 열려 있어야 함
				if (gameBoard[i + 1][j - 1] == "+" || gameBoard[i - 2][j + 2] == "+")
				{
					//만약 2개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
					if (i - 2 == -1 || j + 2 == BOARD_SIZE)
					{
						if (gameBoard[i + 1][j - 1] == "●") {}

						else
						{
							gameBoard[i + 1][j - 1] = "○";
							return 0;
						}
					}
					else if (i + 1 == BOARD_SIZE || j - 1 == -1)
					{
						if (gameBoard[i - 2][j + 2] == "●") {}

						else
						{
							gameBoard[i - 2][j + 2] = "○";
							return 0;
						}
					}

					//만약 2개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
					else if (gameBoard[i + 1][j - 1] == "●")
					{
						gameBoard[i - 2][j + 2] = "○";
						return 0;
					}
					else if (gameBoard[i - 2][j + 2] == "●")
					{
						gameBoard[i + 1][j - 1] = "○";
						return 0;
					}
				}
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk3s()
{
	//가로로 3개일 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○" && gameBoard[i][j + 2] == "○")
			{
				//만약 3개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (j - 1 == -1)
				{
					if (gameBoard[i][j + 3] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i][j + 3] = "○";
						return 0;
					}
				}
				else if (j + 3 == BOARD_SIZE)
				{
					if (gameBoard[i][j - 1] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i][j - 1] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i][j - 1] == "●" && gameBoard[i][j + 3] == "●") {}

				//만약 3개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i][j - 1] == "●")
				{
					gameBoard[i][j + 3] = "○";
					return 0;
				}
				else if (gameBoard[i][j + 3] == "●")
				{
					gameBoard[i][j - 1] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					//[i][j - 1]의 가중치가 더 클 경우
					if (weight[i][j - 1] > weight[i][j + 3])
					{
						gameBoard[i][j - 1] = "○";
						return 0;
					}

					//[i][j + 3]의 가중치가 더 클 경우
					else if (weight[i][j - 1] < weight[i][j + 3])
					{
						gameBoard[i][j + 3] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * i + j - 1;
						saveweight[1] = 100 * i + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}
			}
		}
	}

	//세로로 3개일 경우
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○" && gameBoard[i + 2][j] == "○")
			{
				//만약 3개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (i - 1 == -1)
				{
					if (gameBoard[i + 3][j] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i + 3][j] = "○";
						return 0;
					}
				}
				else if (i + 3 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i - 1][j] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i - 1][j] == "●" && gameBoard[i + 3][j] == "●") {}

				//만약 3개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i - 1][j] == "●")
				{
					gameBoard[i + 3][j] = "○";
					return 0;
				}
				else if (gameBoard[i + 3][j] == "●")
				{
					gameBoard[i - 1][j] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					//[i - 1][j]의 가중치가 더 클 경우
					if (weight[i - 1][j] > weight[i + 3][j])
					{
						gameBoard[i - 1][j] = "○";
						return 0;
					}

					//[i + 3][j]의 가중치가 더 클 경우
					else if (weight[i - 1][j] < weight[i + 3][j])
					{
						gameBoard[i + 3][j] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * (i - 1) + j;
						saveweight[1] = 100 * (i + 3) + j;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}
			}
		}
	}

	//대각선 아래로 3개일 경우
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○" && gameBoard[i + 2][j + 2] == "○")
			{
				//만약 3개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (i - 1 == -1 || j - 1 == -1)
				{
					if (gameBoard[i + 3][j + 3] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i + 3][j + 3] = "○";
						return 0;
					}
				}
				else if (i + 3 == BOARD_SIZE || j + 3 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j - 1] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i - 1][j - 1] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i - 1][j - 1] == "●" && gameBoard[i + 3][j + 3] == "●") {}

				//만약 3개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i - 1][j - 1] == "●")
				{
					gameBoard[i + 3][j + 3] = "○";
					return 0;
				}
				else if (gameBoard[i + 3][j + 3] == "●")
				{
					gameBoard[i - 1][j - 1] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					//[i - 1][j - 1]의 가중치가 더 클 경우
					if (weight[i - 1][j - 1] > weight[i + 3][j + 3])
					{
						gameBoard[i - 1][j - 1] = "○";
						return 0;
					}

					//[i + 3][j + 3]의 가중치가 더 클 경우
					else if (weight[i - 1][j - 1] < weight[i + 3][j + 3])
					{
						gameBoard[i + 3][j + 3] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * (i - 1) + j - 1;
						saveweight[1] = 100 * (i + 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}
			}
		}
	}

	//대각선 위로 3개일 경우
	for (int i = 2; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○" && gameBoard[i - 2][j + 2] == "○")
			{
				//만약 2개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (i - 3 == -1 || j + 3 == BOARD_SIZE)
				{
					if (gameBoard[i + 1][j - 1] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i + 1][j - 1] = "○";
						return 0;
					}
				}
				else if (i + 1 == BOARD_SIZE || j - 1 == -1)
				{
					if (gameBoard[i - 3][j + 3] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i - 3][j + 3] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i + 1][j - 1] == "●" && gameBoard[i - 3][j + 3] == "●") {}

				//만약 2개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i + 1][j - 1] == "●")
				{
					gameBoard[i - 3][j + 3] = "○";
					return 0;
				}
				else if (gameBoard[i - 3][j + 3] == "●")
				{
					gameBoard[i + 1][j - 1] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					//[i + 1][j - 1]의 가중치가 더 클 경우
					if (weight[i + 1][j - 1] > weight[i - 3][j + 3])
					{
						gameBoard[i + 1][j - 1] = "○";
						return 0;
					}

					//[i - 3][j + 3]의 가중치가 더 클 경우
					else if (weight[i + 1][j - 1] < weight[i - 3][j + 3])
					{
						gameBoard[i - 3][j + 3] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * (i + 1) + j - 1;
						saveweight[1] = 100 * (i - 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk4s()
{
	//가로로 4개일 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○" && gameBoard[i][j + 2] == "○" && gameBoard[i][j + 3] == "○")
			{
				//만약 4개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (j - 1 == -1)
				{
					if (gameBoard[i][j + 4] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i][j + 4] = "○";
						return 0;
					}
				}
				else if (j - 1 == BOARD_SIZE)
				{
					if (gameBoard[i][j + 4] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i][j + 4] = "○";
						return 0;
					}
				}

				//만약 4개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i][j - 1] == "●" && gameBoard[i][j + 4] == "●") {}

				//만약 4개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i][j - 1] == "●")
				{
					gameBoard[i][j + 4] = "○";
					return 0;
				}
				else if (gameBoard[i][j + 4] == "●")
				{
					gameBoard[i][j - 1] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					saveweight[0] = 100 * i + j - 1;
					saveweight[1] = 100 * i + j + 4;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}
		}
	}

	//세로로 4개일 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○" && gameBoard[i + 2][j] == "○" && gameBoard[i + 3][j] == "○")
			{
				//만약 4개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (i - 1 == -1)
				{
					if (gameBoard[i + 4][j] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i + 4][j] = "○";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i - 1][j] = "○";
						return 0;
					}
				}

				//만약 4개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i - 1][j] == "●" && gameBoard[i + 4][j] == "●") {}

				//만약 4개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i - 1][j] == "●")
				{
					gameBoard[i + 4][j] = "○";
					return 0;
				}
				else if (gameBoard[i + 4][j] == "●")
				{
					gameBoard[i - 1][j] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					saveweight[0] = 100 * (i - 1) + j;
					saveweight[1] = 100 * (i + 4) + j;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}
		}
	}

	//대각선 아래로 4개일 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○" && gameBoard[i + 2][j + 2] == "○" && gameBoard[i + 3][j + 3] == "○")
			{
				//만약 4개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (i - 1 == -1 || j - 1 == -1)
				{
					if (gameBoard[i + 4][j + 4] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i + 4][j + 4] = "○";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j - 1] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i - 1][j - 1] = "○";
						return 0;
					}
				}

				//만약 4개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i - 1][j - 1] == "●" && gameBoard[i + 4][j + 4] == "●") {}

				//만약 4개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i - 1][j - 1] == "●")
				{
					gameBoard[i + 4][j + 4] = "○";
					return 0;
				}
				else if (gameBoard[i + 4][j + 4] == "●")
				{
					gameBoard[i - 1][j - 1] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					saveweight[0] = 100 * (i - 1) + j - 1;
					saveweight[1] = 100 * (i + 4) + j + 4;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}
		}
	}

	//대각선 위로 4개일 경우
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○" && gameBoard[i - 2][j + 2] == "○" && gameBoard[i - 3][j + 3] == "○")
			{
				//만약 4개의 돌 중 한 쪽 끝이 판의 끝에 막혀 있을 경우
				if (i - 4 == -1 || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i + 1][j - 1] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i + 1][j - 1] = "○";
						return 0;
					}
				}
				else if (i + 1 == BOARD_SIZE || j - 1 == -1)
				{
					if (gameBoard[i - 4][j + 4] == "●") {}	//양 끝이 하나는 벽, 하나는 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.

					else
					{
						gameBoard[i - 4][j + 4] = "○";
						return 0;
					}
				}

				//만약 4개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우, 아무것도 하지 않는다.
				else if (gameBoard[i + 1][j - 1] == "●" && gameBoard[i - 4][j + 4] == "●") {}

				//만약 4개의 돌의 끝 중 한 쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i + 1][j - 1] == "●")
				{
					gameBoard[i - 4][j + 4] = "○";
					return 0;
				}
				else if (gameBoard[i - 4][j + 4] == "●")
				{
					gameBoard[i + 1][j - 1] = "○";
					return 0;
				}

				//막혀 있지 않을 경우
				else
				{
					saveweight[0] = 100 * (i + 1) + j - 1;
					saveweight[1] = 100 * (i - 4) + j + 4;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "○";
					return 0;
				}
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk1_2s()
{
	//가로로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "○" && gameBoard[i][j + 3] == "○")
			{
				gameBoard[i][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "○")
			{
				gameBoard[i][j + 2] = "○";
				return 0;
			}
		}
	}

	//세로로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "○" && gameBoard[i + 3][j] == "○")
			{
				gameBoard[i + 1][j] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "○")
			{
				gameBoard[i + 2][j] = "○";
				return 0;
			}
		}
	}

	//오른쪽 아래 대각선으로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "○" && gameBoard[i + 3][j + 3] == "○")
			{
				gameBoard[i + 1][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "○")
			{
				gameBoard[i + 2][j + 2] = "○";
				return 0;
			}
		}
	}

	//오른쪽 위 대각선으로 1 띄고 2개의 돌 혹은 2 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "○" && gameBoard[i - 3][j + 3] == "○")
			{
				gameBoard[i - 1][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "○")
			{
				gameBoard[i - 2][j + 2] = "○";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk1_3s()
{
	//가로로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "○" && gameBoard[i][j + 3] == "○" && gameBoard[i][j + 4] == "○")
			{
				gameBoard[i][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○" && gameBoard[i][j + 2] == "○" && gameBoard[i][j + 3] == "+" && gameBoard[i][j + 4] == "○")
			{
				gameBoard[i][j + 3] = "○";
				return 0;
			}

			else {}
		}
	}

	//세로로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "○" && gameBoard[i + 3][j] == "○" && gameBoard[i + 4][j] == "○")
			{
				gameBoard[i + 1][j] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○" && gameBoard[i + 2][j] == "○" && gameBoard[i + 3][j] == "+" && gameBoard[i + 4][j] == "○")
			{
				gameBoard[i + 3][j] = "○";
				return 0;
			}

			else {}
		}
	}

	//오른쪽 아래 대각선으로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "○" && gameBoard[i + 3][j + 3] == "○" && gameBoard[i + 4][j + 4] == "○")
			{
				gameBoard[i + 1][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○" && gameBoard[i + 2][j + 2] == "○" && gameBoard[i + 3][j + 3] == "+" && gameBoard[i + 4][j + 4] == "○")
			{
				gameBoard[i + 3][j + 3] = "○";
				return 0;
			}

			else {}
		}
	}

	//오른쪽 위 대각선으로 1 띄고 3개의 돌 혹은 3 띄고 1개의 돌이 나란히 놓여 있을 경우
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "○" && gameBoard[i - 3][j + 3] == "○" && gameBoard[i - 4][j + 4] == "○")
			{
				gameBoard[i - 1][j + 1] = "○";
				return 0;
			}

			else if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○" && gameBoard[i - 2][j + 2] == "○" && gameBoard[i - 3][j + 3] == "+" && gameBoard[i - 4][j + 4] == "○")
			{
				gameBoard[i - 3][j + 3] = "○";
				return 0;
			}

			else {}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk2_2s()
{
	//가로로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "○" && gameBoard[i][j + 4] == "○")
			{
				gameBoard[i][j + 2] = "○";
				return 0;
			}
		}
	}

	//세로로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "○" && gameBoard[i + 4][j] == "○")
			{
				gameBoard[i + 2][j] = "○";
				return 0;
			}
		}
	}

	//오른쪽 아래 대각선으로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "○" && gameBoard[i + 4][j + 4] == "○")
			{
				gameBoard[i + 2][j + 2] = "○";
				return 0;
			}
		}
	}

	//오른쪽 위 대각선으로 2 띄고 2개의 돌이 나란히 놓여 있을 경우
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "○" && gameBoard[i - 4][j + 4] == "○")
			{
				gameBoard[i - 2][j + 2] = "○";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk1_1s()
{
	//가로로 1 띄고 1개일 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 2] == "○")
			{
				//+○+○+일 경우, 오른쪽 혹은 왼쪽 +에 착수한다.
				if (gameBoard[i][j - 1] == "+" && gameBoard[i][j + 3] == "+")
				{
					//[i][j - 1]의 가중치가 더 클 경우
					if (weight[i][j - 1] > weight[i][j + 3])
					{
						gameBoard[i][j - 1] = "○";
						return 0;
					}

					//[i][j + 3]의 가중치가 더 클 경우
					else if (weight[i][j - 1] < weight[i][j + 3])
					{
						gameBoard[i][j + 3] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * i + j - 1;
						saveweight[1] = 100 * i + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i][j - 1] == "●" && gameBoard[i][j + 3] == "●") {}

				//만약 한쪽 끝이 벽이 막혀 있을 경우
				else if (j - 1 == -1 || j + 3 == BOARD_SIZE) {}

				//○+○일 경우, 가운데 +에 착수한다.
				else
				{
					gameBoard[i][j + 1] = "○";
					return 0;
				}
			}
		}
	}

	//세로로 1 띄고 1개일 경우
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "○")
			{
				//+○+○+일 경우, 위 혹은 아래 +에 착수한다.
				if (gameBoard[i - 1][j] == "+" && gameBoard[i + 3][j] == "+")
				{
					//[i - 1][j]의 가중치가 더 클 경우
					if (weight[i - 1][j] > weight[i + 3][j])
					{
						gameBoard[i - 1][j] = "○";
						return 0;
					}

					//[i + 3][j]의 가중치가 더 클 경우
					else if (weight[i - 1][j] < weight[i + 3][j])
					{
						gameBoard[i + 3][j] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * (i - 1) + j;
						saveweight[1] = 100 * (i + 3) + j;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i - 1][j] == "●" && gameBoard[i + 3][j] == "●") {}

				//만약 한쪽 끝이 벽이 막혀 있을 경우
				else if (i - 1 == -1 || i + 3 == BOARD_SIZE) {}

				//○+○일 경우, 가운데 +에 착수한다.
				else
				{
					gameBoard[i + 1][j] = "○";
					return 0;
				}
			}
		}
	}

	//오른쪽 아래로 1 띄고 1개일 경우
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "○")
			{
				//+○+○+일 경우, 오른쪽 아래 혹은 왼쪽 위 +에 착수한다.
				if (gameBoard[i - 1][j - 1] == "+" && gameBoard[i + 3][j + 3] == "+")
				{
					//[i - 1][j - 1]의 가중치가 더 클 경우
					if (weight[i - 1][j - 1] > weight[i + 3][j + 3])
					{
						gameBoard[i - 1][j - 1] = "○";
						return 0;
					}

					//[i + 3][j + 3]의 가중치가 더 클 경우
					else if (weight[i - 1][j - 1] < weight[i + 3][j + 3])
					{
						gameBoard[i + 3][j + 3] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * (i - 1) + j - 1;
						saveweight[1] = 100 * (i + 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i - 1][j - 1] == "●" && gameBoard[i + 3][j + 3] == "●") {}

				//만약 한쪽 끝이 벽이 막혀 있을 경우
				else if (i - 1 == -1 || j - 1 == -1 || i + 3 == BOARD_SIZE || j + 3 == BOARD_SIZE) {}

				//○+○일 경우, 가운데 +에 착수한다.
				else
				{
					gameBoard[i + 1][j + 1] = "○";
					return 0;
				}
			}
		}
	}

	//오른쪽 위로 1 띄고 1개일 경우
	for (int i = 2; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "○")
			{
				//+○+○+일 경우, 오른쪽 위 혹은 왼쪽 아래 +에 착수한다.
				if (gameBoard[i + 1][j - 1] == "+" && gameBoard[i - 3][j + 3] == "+")
				{
					//[i + 1][j - 1]의 가중치가 더 클 경우
					if (weight[i + 1][j - 1] > weight[i - 3][j + 3])
					{
						gameBoard[i + 1][j - 1] = "○";
						return 0;
					}

					//[i - 3][j + 3]의 가중치가 더 클 경우
					else if (weight[i + 1][j - 1] < weight[i - 3][j + 3])
					{
						gameBoard[i - 3][j + 3] = "○";
						return 0;
					}

					//두 가중치가 같을 경우
					else
					{
						saveweight[0] = 100 * (i + 1) + j - 1;
						saveweight[1] = 100 * (i - 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "○";
						return 0;
					}
				}

				//만약 3개의 돌의 양쪽 끝이 사용자의 돌에 의해 막혀 있을 경우
				else if (gameBoard[i + 1][j - 1] == "●" && gameBoard[i - 3][j + 3] == "●") {}

				//만약 한쪽 끝이 벽이 막혀 있을 경우
				else if (i - 3 == -1 || j - 1 == -1 || i + 1 == BOARD_SIZE || j + 3 == BOARD_SIZE) {}

				//○+○일 경우, 가운데 +에 착수한다.
				else
				{
					gameBoard[i - 1][j + 1] = "○";
					return 0;
				}
			}
		}
	}

	return 0;
}

int Game_Board::count_cpustone()
{
	int count = 0;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○")
				count++;
		}
	}

	return count;
}

bool Game_Board::win_player()
{
	//가로로 5개인 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i][j + 1] == "●" && gameBoard[i][j + 2] == "●" && gameBoard[i][j + 3] == "●" && gameBoard[i][j + 4] == "●")
				return 1;
		}
	}

	//세로로 5개인 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j] == "●" && gameBoard[i + 2][j] == "●" && gameBoard[i + 3][j] == "●" && gameBoard[i + 4][j] == "●")
				return 1;
		}
	}

	//오른쪽 아래 대각선으로 5개인 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i + 1][j + 1] == "●" && gameBoard[i + 2][j + 2] == "●" && gameBoard[i + 3][j + 3] == "●" && gameBoard[i + 4][j + 4] == "●")
				return 1;
		}
	}

	//오른쪽 위 대각선으로 5개인 경우
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "●" && gameBoard[i - 1][j + 1] == "●" && gameBoard[i - 2][j + 2] == "●" && gameBoard[i - 3][j + 3] == "●" && gameBoard[i - 4][j + 4] == "●")
				return 1;
		}
	}

	return 0;
}

bool Game_Board::win_cpu()
{
	//가로로 5개인 경우
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i][j + 1] == "○" && gameBoard[i][j + 2] == "○" && gameBoard[i][j + 3] == "○" && gameBoard[i][j + 4] == "○")
				return 1;
		}
	}

	//세로로 5개인 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j] == "○" && gameBoard[i + 2][j] == "○" && gameBoard[i + 3][j] == "○" && gameBoard[i + 4][j] == "○")
				return 1;
		}
	}

	//오른쪽 아래 대각선으로 5개인 경우
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i + 1][j + 1] == "○" && gameBoard[i + 2][j + 2] == "○" && gameBoard[i + 3][j + 3] == "○" && gameBoard[i + 4][j + 4] == "○")
				return 1;
		}
	}

	//오른쪽 위 대각선으로 5개인 경우
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "○" && gameBoard[i - 1][j + 1] == "○" && gameBoard[i - 2][j + 2] == "○" && gameBoard[i - 3][j + 3] == "○" && gameBoard[i - 4][j + 4] == "○")
				return 1;
		}
	}

	return 0;
}

int main()
{
	Game_Board omok;

	int count_playerstone = 0;	//사용자의 돌의 개수

	while (true)
	{
		omok.printGB();		//게임판을 표시
		omok.resetw();		//가중치 초기화
		omok.resets();		//saveweight[]초기화

		if (omok.win_cpu() == 1)	//컴퓨터의 돌이 오목 이상이라면
		{
			cout << endl << "당신의 패배입니다." << endl;
			break;
		}

		omok.player_chakshu();	//사용자 착수
		count_playerstone++;	//사용자의 돌 개수 증가
		omok.weighting();		//가중치 부여

		if (omok.win_player() == 1)	//사용자의 돌이 오목 이상이라면
		{
			omok.printGB();
			cout << endl << "축하합니다!" << endl << "당신의 승리입니다." << endl;
			break;
		}

		//자기 차례에 자신의 돌이 5개가 된다면 공격한다.
		omok.cpu_chackshu_atk1_3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk2_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk4s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//다음 차례에 상대가 5개가 되면 막는다.
		omok.cpu_chackshu_def4s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_def1_3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_def2_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//다음 차례에 상대가 4개가 되면 막는다.
		omok.cpu_chackshu_def1_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//자기 차례에 자신의 돌이 4개가 된다면 공격한다.
		omok.cpu_chackshu_atk1_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//양 쪽 끝이 열린 3목이 있으면 막는다.
		omok.cpu_chackshu_def3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//방어할 것이 없다면 2개의 돌을 3개로 만들어 공격한다.
		omok.cpu_chackshu_atk1_1s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//위의 해당사항이 없다면 가중치에 의해 착수한다.
		omok.cpu_chakshu_weight();
		if (omok.count_cpustone() == count_playerstone)
			continue;
	}

	return 0;
}