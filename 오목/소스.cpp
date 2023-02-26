#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define BOARD_SIZE 19
/*2020112027 �ڻ��*/

class Game_Board	//�ٵ��ǿ� ���õ� Ŭ����
{
private:
	int inputrow;	//�Է¹޴� ���� ��
	int inputcol;	//�Է¹޴� ���� ��
public:
	string gameBoard[BOARD_SIZE][BOARD_SIZE];	//�����ǿ� �򵹰� �������� ǥ�����ִ� �迭
	int weight[BOARD_SIZE][BOARD_SIZE];			//�������� �� ĭ�� ����ġ�� �Ҵ��ϴ� �迭
	int saveweight[100];						//�� �� �ִ� ��ġ���� �����ϴ� �迭
	
	Game_Board();			//�ٵ����� ��� ������ +�� �ʱ�ȭ

	void printGB();			//���� �ٵ��ǿ� ������ �����ִ� ��Ȳ�� ����ϴ� �Լ�
	int player_chakshu();	//������� ���ʿ� �� �浹�� ��ǥ�� �Է¹޴� �Լ�
	void weighting();		//������ ���� �����ִ� ��Ȳ�� ���� �浹 �ֺ� 8���� +2, �鵹 �ֺ� 8���� -2�� �ϴ� �Լ�
	void printw();			//������ ���� �ִ� ��Ȳ�� ����ġ�� ���������� ǥ�����ִ� �Լ�
	void resetw();			//��� ����ġ�� 0���� �ʱ�ȭ�ϴ� �Լ�
	void resets();			//��� saveweight[]�� �ʱ�ȭ�ϴ� �迭
	int cpu_chakshu_weight();	//����ġ�� �̿��Ͽ� ��ǻ�Ͱ� �����Ѵ�.
	int cpu_chackshu_def3s();	//������� ���� 3���� ���� ������ ���� �� ��ǻ�Ͱ� ����Ѵ�.
	int cpu_chackshu_def4s();	//������� ���� 4���� ���� ������ ���� �� ��ǻ�Ͱ� ����Ѵ�.
	int cpu_chackshu_def1_2s();	//������� ���� 1 ��� 2���� ���� ������ ���� �� ��ǻ�Ͱ� ����Ѵ�.
	int cpu_chackshu_def1_3s();	//������� ���� 1 ��� 3���� ���� ������ ���� �� ��ǻ�Ͱ� ����Ѵ�.
	int cpu_chackshu_def2_2s();	//������� ���� 2 ��� 2���� ���� ������ ���� �� ��ǻ�Ͱ� ����Ѵ�.
	int cpu_chackshu_atk2s();	//������ 2���� ��ǻ���� ���� �� �� ���� ������� ���� ����, ����� �ʿ䰡 ���� ���, �����Ѵ�.
	int cpu_chackshu_atk3s();	//������ 3���� ��ǻ���� ���� �ְ�, ����� �ʿ䰡 ���� ���, �����Ѵ�.
	int cpu_chackshu_atk4s();	//������ 4���� ��ǻ���� ���� ���� ��� �����Ѵ�.
	int cpu_chackshu_atk1_2s();	//������ 1 ��� 2���� ��ǻ���� ���� �ְ�, ����� �ʿ䰡 ���� ���, �����Ѵ�.
	int cpu_chackshu_atk1_3s();	//������ 1 ��� 3���� ��ǻ���� ���� ���� ��� �����Ѵ�.
	int cpu_chackshu_atk2_2s();	//������ 2 ��� 2���� ��ǻ���� ���� ���� ��� �����Ѵ�.
	int cpu_chackshu_atk1_1s();	//������ 1 ��� 1���� ��ǻ���� ���� �ְ�, ����� �ʿ䰡 ���� ���, �����Ѵ�.
	int count_cpustone();		//�����ǿ��� ���� ��ǻ���� ���� ������ ���� �Լ�.
	bool win_player();		//������� ���� 5���� ������ ������ �¸��Ѵ�.
	bool win_cpu();			//��ǻ���� ���� 5���� ������ ������ �¸��Ѵ�.
};

Game_Board::Game_Board()	//gameBoard �迭�� +�� �ʱ�ȭ
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

void Game_Board::printGB()	//�ٵ��� ���
{
	cout << endl << "      ";
	for (int i = 0; i < BOARD_SIZE; i++)	//���� ��ǥ ���
	{
		if (i < 10)		//���� ��ǥ�� 10���� ���� ��� 0�� ���δ�.
			cout << " 0" << i;
		else			//���� ��ǥ�� 10�̻��� ��� �׳� ����Ѵ�.
			cout << " " << i;
	}
	cout << endl;

	if (BOARD_SIZE % 2 == 0)	//BOARD_SIZE�� ¦�����
	{
		cout << "�ѤѤ�";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
			cout << "�ѤѤ�";
	}
	else						//BOARD_SIZE�� Ȧ�����
	{
		cout << "�ѤѤѤѤ�";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
		{
			cout << "�ѤѤ�";
		}
	}
	cout << endl;
	
	for (int i = 0; i < BOARD_SIZE; i++)	//���� ��ǥ ���
	{
		if (i < 10)		//���� ��ǥ�� 10���� ���� ��� 0�� ���δ�.
			cout << " 0" << i << " | ";
		else			//���� ��ǥ�� 10�̻��� ��� �׳� ����Ѵ�.
			cout << " " << i << " | ";

		for (int j = 0; j < BOARD_SIZE; j++)	//�浹, �鵹 ���
		{
			if (gameBoard[i][j] == "��" || gameBoard[i][j] == "��")
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
		cout << "����� �����Դϴ�." << endl;
		cout << "������ ��ġ�� �����ϼ���." << endl;
		cin >> inputrow >> inputcol;	//������ ��ġ(����, ����)�� �Է¹޴´�.

		if (gameBoard[inputcol][inputrow] == "��" || gameBoard[inputcol][inputrow] == "��")	//���� �ִ� �ڸ����� ������ �� ����.
		{
			cout << "�� ���� ���� �־� ������ �� �����ϴ�." << endl;
			continue;
		}

		else if (inputcol >= 19 || inputcol < 0 || inputrow >= 19 || inputcol < 0)	//�������� �ۿ��� ������ �� ����.
		{
			cout << "�� ���� �������� ���Դϴ�." << endl;
			continue;
		}

		else
		{
			break;
		}
	}

	gameBoard[inputcol][inputrow] = "��";	//�Է¹��� ��ġ�� �����Ѵ�.
	return 0;
}

void Game_Board::weighting()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��")	//����ڰ� ������ ���� �ѷ��ΰ� �ִ� 8���� +2�� ����ġ
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
			
			else if (gameBoard[i][j] == "��")	//��ǻ�Ͱ� ������ ���� �ѷ��ΰ� �ִ� 8���� -2�� ����ġ
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

	for (int i = 0; i < BOARD_SIZE; i++)	//���� �̹� �ִ� �ڸ��� ����ġ�� -99�� �����.
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" || gameBoard[i][j] == "��")
			{
				weight[i][j] = -99;
			}
		}
	}
}

void Game_Board::printw()	//����ġ�� ���������� ���
{
	cout << endl << "      ";
	for (int i = 0; i < BOARD_SIZE; i++)	//���� ��ǥ ���
	{
		if (i < 10)
			cout << " 0" << i;
		else
			cout << " " << i;
	}
	cout << endl;

	if (BOARD_SIZE % 2 == 0)
	{
		cout << "�ѤѤ�";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
			cout << "�ѤѤ�";
	}
	else
	{
		cout << "�ѤѤѤѤ�";
		for (int i = 0; i < BOARD_SIZE / 2; i++)
		{
			cout << "�ѤѤ�";
		}
	}
	cout << endl;

	for (int i = 0; i < BOARD_SIZE; i++)	//���� ��ǥ ���
	{
		if (i < 10)
			cout << " 0" << i << " | ";
		else
			cout << " " << i << " | ";

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (weight[i][j] > 0)		//����ġ�� ����� ����� ����ġ ���
				cout << " +" << weight[i][j];

			else if (weight[i][j] == 0)	//����ġ�� 0�� ����� ����ġ ���
				cout << "  " << weight[i][j];

			else if (weight[i][j] < 0)	//����ġ�� ������ ����� ����ġ ���
				cout << " " << weight[i][j];
		}

		cout << endl;
	}
}

void Game_Board::resetw()	//��� ����ġ�� 0���� �ʱ�ȭ
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			weight[i][j] = 0;
		}
	}
}

void Game_Board::resets()	//��� saveweight[]�� �ʱ�ȭ
{
	for (int i = 0; i < 100; i++)
		saveweight[i] = 0;
}

int Game_Board::cpu_chakshu_weight()
{
	int max = weight[0][0];	//�ʱ��� max���� weight[0][0]���� ����
	int count = 0;			//weight���� �� ���� ū ���� ����

	
	for (int i = 0; i < BOARD_SIZE; i++)	//��� weight�� ���ؼ� ���� ū weight�� ã��
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			if (max < weight[i][j + 1])
				max = weight[i][j + 1];
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)	//���� ū weight���� ���� weight������ ã��
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			if (max == weight[i][j])
			{
				saveweight[count] = 100 * i + j;	//saveweight �迭�� i�� j���� ���� �ڸ������� j, ���� �ڸ����ʹ� i�� �������� �����Ѵ�.
				count++;	//count���� 1 ������Ų��.
			}
		}
	}

	srand(time(NULL));
	int random = rand() % count;	//0���� count-1������ ���� �� �ϳ��� �������� �̴´�.

	int b = saveweight[random] % 100;			//�������� ���� j�� ���ϰ� b�� �����Ѵ�.
	int a = (saveweight[random] - b) / 100;		//�������� ���� i�� ���ϰ� a�� �����Ѵ�.

	gameBoard[a][b] = "��";		//�۵��� ��ǻ�Ͱ� �����Ѵ�.
	return 0;
}

int Game_Board::cpu_chackshu_def3s()
{
	//���η� 3���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��")
			{
				//���� 3���� ���� �� �� �� �� ���� ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				if (j - 1 == -1 || j + 3 == BOARD_SIZE) {}

				//���� 3���� ���� �� �� �� �� ���� �̹� ��ǻ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				else if (gameBoard[i][j - 1] == "��" || gameBoard[i][j + 3] == "��") {}

				//4���� ���� �˻����� �ʴ´�.
				else if (gameBoard[i][j - 1] == "��" || gameBoard[i][j + 3] == "��") {}

				//���� ���� ���� ��� �� �� �� �� �ʿ� �������� �����Ѵ�.
				else
				{
					saveweight[0] = 100 * i + j - 1;
					saveweight[1] = 100 * i + j + 3;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[a][b] = "��";
					}
					return 0;
				}
			}
		}
	}

	//���η� 3���� ���
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��")
			{
				//���� 3���� ���� �� �� �� �� ���� ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				if (i - 1 == -1 || i + 3 == BOARD_SIZE) {}

				//���� 3���� ���� �� �� �� �� ���� �̹� ��ǻ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				else if (gameBoard[i - 1][j] == "��" || gameBoard[i + 3][j] == "��") {}

				//4���� ���� �˻����� �ʴ´�.
				else if (gameBoard[i - 1][j] == "��" || gameBoard[i + 3][j] == "��") {}

				//���� ���� ���� ��� �� �� �� �� �ʿ� �������� �����Ѵ�.
				else
				{
					saveweight[0] = 100 * (i - 1) + j;
					saveweight[1] = 100 * (i + 3) + j;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[a][b] = "��";
					}
					return 0;
				}
			}
		}
	}

	//������ �Ʒ� �밢������ 3���� ���
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��")
			{
				//���� 3���� ���� �� �� �� �� ���� ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				if (i - 1 == -1 || j - 1 == -1 || i + 3 == BOARD_SIZE || j + 3 == BOARD_SIZE) {}

				//���� 3���� ���� �� �� �� �� ���� �̹� ��ǻ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				else if (gameBoard[i - 1][j - 1] == "��" || gameBoard[i + 3][j + 3] == "��") {}

				//4���� ���� �˻����� �ʴ´�.
				else if (gameBoard[i - 1][j - 1] == "��" || gameBoard[i + 3][j + 3] == "��") {}

				//���� ���� ���� ��� �� �� �� �� �ʿ� �������� �����Ѵ�.
				else
				{
					saveweight[0] = 100 * (i - 1) + j - 1;
					saveweight[1] = 100 * (i + 3) + j + 3;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[a][b] = "��";
					}
					return 0;
				}
			}
		}
	}

	//������ �� �밢������ 3���� ���
	for (int i = 2; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��")
			{
				//���� 3���� ���� �� �� �� �� ���� ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				if (i + 1 == BOARD_SIZE || j - 1 == -1 || i - 3 == -1 || j + 3 == BOARD_SIZE) {}

				//���� 3���� ���� �� �� �� �� ���� �̹� ��ǻ���� ���� ���� �ִٸ� ���� ���� �ʿ䰡 ����.
				else if (gameBoard[i + 1][j - 1] == "��" || gameBoard[i - 3][j + 3] == "��") {}
				
				//4���� ���� �˻����� �ʴ´�.
				else if (gameBoard[i + 1][j - 1] == "��" || gameBoard[i - 3][j + 3] == "��") {}

				//���� ���� ���� ��� �� �� �� �� �ʿ� �������� �����Ѵ�.
				else
				{
					saveweight[0] = 100 * (i + 1) + j - 1;
					saveweight[1] = 100 * (i - 3) + j + 3;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					if (gameBoard[a][b] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[a][b] = "��";
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
	//���η� 4���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��")
			{
				//4���� ���� �� �� ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				if (j - 1 == -1)
				{
					if (gameBoard[i][j + 4] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i][j + 4] = "��";
						return 0;
					}
				}
				else if (j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i][j - 1] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i][j - 1] = "��";
						return 0;
					}
				}

				//4���� ���� �� �� ���� ��ǻ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				else if (gameBoard[i][j - 1] == "��")
				{
					if (gameBoard[i][j + 4] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i][j + 4] = "��";
						return 0;
					}
				}
				else if (gameBoard[i][j + 4] == "��")
				{
					if (gameBoard[i][j - 1] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i][j - 1] = "��";
						return 0;
					}
				}

				else {}
			}
		}
	}

	//���η� 4���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��")
			{
				//4���� ���� �� �� ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				if (i - 1 == -1)
				{
					if (gameBoard[i + 4][j] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i + 4][j] = "��";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i - 1][j] = "��";
						return 0;
					}
				}

				//4���� ���� �� �� ���� ��ǻ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				else if (gameBoard[i - 1][j] == "��")
				{
					if (gameBoard[i + 4][j] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i + 4][j] = "��";
						return 0;
					}
				}
				else if (gameBoard[i + 4][j] == "��")
				{
					if (gameBoard[i - 1][j] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i - 1][j] = "��";
						return 0;
					}
				}

				else {}
			}
		}
	}

	//������ �Ʒ� �밢������ 4���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��")
			{
				//4���� ���� �� �� ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				if (i - 1 == -1 || j - 1 == -1)
				{
					if (gameBoard[i + 4][j + 4] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i + 4][j + 4] = "��";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j - 1] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i - 1][j - 1] = "��";
						return 0;
					}
				}

				//4���� ���� �� �� ���� ��ǻ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				else if (gameBoard[i - 1][j - 1] == "��")
				{
					if (gameBoard[i + 4][j + 4] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i + 4][j + 4] = "��";
						return 0;
					}
				}
				else if (gameBoard[i + 4][j + 4] == "��")
				{
					if (gameBoard[i - 1][j - 1] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i - 1][j - 1] = "��";
						return 0;
					}
				}

				else {}
			}
		}
	}

	//������ �� �밢������ 4���� ���
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��")
			{
				//���� 4���� ���� �� �� ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				if (i + 1 == BOARD_SIZE || j - 1 == -1)
				{
					if (gameBoard[i - 4][j + 4] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i - 4][j + 4] = "��";
						return 0;
					}
				}
				else if (i - 4 == -1 || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i + 1][j - 1] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i + 1][j - 1] = "��";
						return 0;
					}
				}

				//4���� ���� �� �� ���� ��ǻ���� ���� ���� �ִٸ� �ٸ� �� �ʸ� ������ �ȴ�.
				else if (gameBoard[i + 1][j - 1] == "��")
				{
					if (gameBoard[i - 4][j + 4] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i - 4][j + 4] = "��";
						return 0;
					}
				}

				else if (gameBoard[i - 4][j + 4] == "��")
				{
					if (gameBoard[i + 1][j - 1] == "+")	//���� �ڸ��� ��� �ִٸ� �����Ѵ�.
					{
						gameBoard[i + 1][j - 1] = "��";
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
	//���η� 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i][j - 1] == "��" || gameBoard[i][j + 4] == "��") {}

				else
				{
					gameBoard[i][j + 1] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i][j - 1] == "��" || gameBoard[i][j + 4] == "��") {}

				else
				{
					gameBoard[i][j + 2] = "��";
					return 0;
				}
			}

			else {}
		}
	}

	//���η� 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i + 1][j] == "��" || gameBoard[i + 4][j] == "��") {}

				else
				{
					gameBoard[i + 1][j] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i + 1][j] == "��" || gameBoard[i + 4][j] == "��") {}
				
				else
				{
					gameBoard[i + 2][j] = "��";
					return 0;
				}
			}

			else {}
		}
	}

	//������ �Ʒ� �밢������ 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i - 1][j - 1] == "��" || gameBoard[i + 4][j + 4] == "��") {}

				else
				{
					gameBoard[i + 1][j + 1] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i - 1][j - 1] == "��" || gameBoard[i + 4][j + 4] == "��") {}

				else
				{
					gameBoard[i + 2][j + 2] = "��";
					return 0;
				}
			}

			else {}
		}
	}

	//������ �� �밢������ 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i + 1][j - 1] == "��" || gameBoard[i - 4][j + 4] == "��") {}

				else
				{
					gameBoard[i - 1][j + 1] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "��")
			{
				//���� 1 ��� 2���� ���� �� �� �ϳ��� ���� ������ ���� ���� �ʿ䰡 ����.
				if (gameBoard[i + 1][j - 1] == "��" || gameBoard[i - 4][j + 4] == "��") {}

				else
				{
					gameBoard[i - 2][j + 2] = "��";
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
	//���η� 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��" && gameBoard[i][j + 4] == "��")
			{
					gameBoard[i][j + 1] = "��";
					return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "+" && gameBoard[i][j + 4] == "��")
			{

				gameBoard[i][j + 3] = "��";
				return 0;
			}
		}
	}

	//���η� 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��" && gameBoard[i + 4][j] == "��")
			{
				gameBoard[i + 1][j] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "+" && gameBoard[i + 4][j] == "��")
			{
				gameBoard[i + 3][j] = "��";
				return 0;
			}
		}
	}

	//������ �Ʒ� �밢������ 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��" && gameBoard[i + 4][j + 4] == "��")
			{
				gameBoard[i + 1][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "+" && gameBoard[i + 4][j + 4] == "��")
			{
				gameBoard[i + 3][j + 3] = "��";
				return 0;
			}
		}
	}

	//������ �� �밢������ 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��" && gameBoard[i - 4][j + 4] == "��")
			{
				gameBoard[i - 1][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "+" && gameBoard[i - 4][j + 4] == "��")
			{
				gameBoard[i - 3][j + 3] = "��";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_def2_2s()
{
	//���η� 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "��" && gameBoard[i][j + 4] == "��")
			{
				gameBoard[i][j + 2] = "��";
				return 0;
			}
		}
	}

	//���η� 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "��" && gameBoard[i + 4][j] == "��")
			{
				gameBoard[i + 2][j] = "��";
				return 0;
			}
		}
	}

	//������ �Ʒ� �밢������ 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "��" && gameBoard[i + 4][j + 4] == "��")
			{
				gameBoard[i + 2][j + 2] = "��";
				return 0;
			}
		}
	}

	//������ �� �밢������ 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "��" && gameBoard[i - 4][j + 4] == "��")
			{
				gameBoard[i - 2][j + 2] = "��";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk2s()
{
	//���η� 2���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			//���� ���� ���� ���
			if (gameBoard[i][j - 1] == "+" && gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "+")
			{
				//[i][j - 1]�� ����ġ�� �� Ŭ ���
				if (weight[i][j - 1] > weight[i][j + 2])
				{
					gameBoard[i][j - 1] = "��";
					return 0;
				}

				//[i][j + 2]�� ����ġ�� �� Ŭ ���
				else if (weight[i][j - 1] < weight[i][j + 2])
				{
					gameBoard[i][j + 2] = "��";
					return 0;
				}

				//�� ����ġ�� ���� ���
				else
				{
					saveweight[0] = 100 * i + j - 1;
					saveweight[1] = 100 * i + j + 2;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��")
			{
				//�� �� ���� ���� �־�� ��
				if (gameBoard[i][j - 1] == "+" || gameBoard[i][j + 2] == "+")
				{
					//���� 2���� �� �� �� �� ���� ���� ���� ���� ���� ���
					if (j - 1 == -1)
					{
						if (gameBoard[i][j + 2] == "��") {}

						else
						{
							gameBoard[i][j + 2] = "��";
							return 0;
						}
					}
					else if (j + 2 == BOARD_SIZE)
					{
						if (gameBoard[i][j - 1] == "��") {}

						else
						{
							gameBoard[i][j - 1] = "��";
							return 0;
						}
					}

					//���� 2���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
					else if (gameBoard[i][j - 1] == "��")
					{
						gameBoard[i][j + 2] = "��";
						return 0;
					}
					else if (gameBoard[i][j + 2] == "��")
					{
						gameBoard[i][j - 1] = "��";
						return 0;

					}
				}
			}
		}
	}

	//���η� 2���� ���
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//���� ���� ���� ���
			if (gameBoard[i - 1][j] == "+" && gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "+")
			{
				//[i - 1][j]�� ����ġ�� �� Ŭ ���
				if (weight[i - 1][j] > weight[i + 2][j])
				{
					gameBoard[i - 1][j] = "��";
					return 0;
				}

				//[i + 2][j]�� ����ġ�� �� Ŭ ���
				else if (weight[i - 1][j] < weight[i + 2][j])
				{
					gameBoard[i + 2][j] = "��";
					return 0;
				}

				//�� ����ġ�� ���� ���
				else
				{
					saveweight[0] = 100 * (i - 1) + j;
					saveweight[1] = 100 * (i + 2) + j;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��")
			{
				//�� �� ���� ���� �־�� ��
				if (gameBoard[i - 1][j] == "+" || gameBoard[i + 2][j] == "+")
				{
					//���� 2���� �� �� �� �� ���� ���� ���� ���� ���� ���
					if (i - 1 == -1)
					{
						if (gameBoard[i + 2][j] == "��") {}

						else
						{
							gameBoard[i + 2][j] = "��";
							return 0;
						}
					}
					else if (i + 2 == BOARD_SIZE)
					{
						if (gameBoard[i - 1][j] == "��") {}

						else
						{
							gameBoard[i - 1][j] = "��";
							return 0;
						}
					}

					//���� 2���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
					else if (gameBoard[i - 1][j] == "��")
					{
						gameBoard[i + 2][j] = "��";
						return 0;
					}
					else if (gameBoard[i + 2][j] == "��")
					{
						gameBoard[i - 1][j] = "��";
						return 0;
					}
				}
			}
		}
	}

	//�밢�� �Ʒ��� 2���� ���
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			//���� ���� ���� ���
			if (gameBoard[i - 1][j - 1] == "+" && gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "+")
			{
				//[i - 1][j - 1]�� ����ġ�� �� Ŭ ���
				if (weight[i - 1][j - 1] > weight[i + 2][j + 2])
				{
					gameBoard[i - 1][j - 1] = "��";
					return 0;
				}

				//[i + 2][j + 2]�� ����ġ�� �� Ŭ ���
				else if (weight[i - 1][j - 1] < weight[i + 2][j + 2])
				{
					gameBoard[i + 2][j + 2] = "��";
					return 0;
				}

				//�� ����ġ�� ���� ���
				else
				{
					saveweight[0] = 100 * (i - 1) + j - 1;
					saveweight[1] = 100 * (i + 2) + j + 2;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��")
			{
				//�� �� ���� ���� �־�� ��
				if (gameBoard[i - 1][j - 1] == "+" || gameBoard[i + 2][j + 2] == "+")
				{
					//���� 2���� �� �� �� �� ���� ���� ���� ���� ���� ���
					if (i - 1 == -1 || j - 1 == -1)
					{
						if (gameBoard[i + 2][j + 2] == "��") {}

						else
						{
							gameBoard[i + 2][j + 2] = "��";
							return 0;
						}
					}
					else if (i + 2 == BOARD_SIZE || j + 2 == BOARD_SIZE)
					{
						if (gameBoard[i - 1][j - 1] == "��") {}

						else
						{
							gameBoard[i - 1][j - 1] = "��";
							return 0;
						}
					}

					//���� 2���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
					else if (gameBoard[i - 1][j - 1] == "��")
					{
						gameBoard[i + 2][j + 2] = "��";
						return 0;
					}
					else if (gameBoard[i + 2][j + 2] == "��")
					{
						gameBoard[i - 1][j - 1] = "��";
						return 0;
					}
				}
			}
		}
	}

	//�밢�� ���� 2���� ���
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 1; j++)
		{
			//���� ���� ���� ���
			if (gameBoard[i + 1][j - 1] == "+" && gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "+")
			{
				//[i + 1][j - 1]�� ����ġ�� �� Ŭ ���
				if (weight[i + 1][j - 1] > weight[i - 2][j + 2])
				{
					gameBoard[i + 1][j - 1] = "��";
					return 0;
				}

				//[i - 2][j + 2]�� ����ġ�� �� Ŭ ���
				else if (weight[i + 1][j - 1] < weight[i - 2][j + 2])
				{
					gameBoard[i - 2][j + 2] = "��";
					return 0;
				}

				//�� ����ġ�� ���� ���
				else
				{
					saveweight[0] = 100 * (i + 1) + j - 1;
					saveweight[1] = 100 * (i - 2) + j + 2;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��")
			{
				//�� �� ���� ���� �־�� ��
				if (gameBoard[i + 1][j - 1] == "+" || gameBoard[i - 2][j + 2] == "+")
				{
					//���� 2���� �� �� �� �� ���� ���� ���� ���� ���� ���
					if (i - 2 == -1 || j + 2 == BOARD_SIZE)
					{
						if (gameBoard[i + 1][j - 1] == "��") {}

						else
						{
							gameBoard[i + 1][j - 1] = "��";
							return 0;
						}
					}
					else if (i + 1 == BOARD_SIZE || j - 1 == -1)
					{
						if (gameBoard[i - 2][j + 2] == "��") {}

						else
						{
							gameBoard[i - 2][j + 2] = "��";
							return 0;
						}
					}

					//���� 2���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
					else if (gameBoard[i + 1][j - 1] == "��")
					{
						gameBoard[i - 2][j + 2] = "��";
						return 0;
					}
					else if (gameBoard[i - 2][j + 2] == "��")
					{
						gameBoard[i + 1][j - 1] = "��";
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
	//���η� 3���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��")
			{
				//���� 3���� ���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (j - 1 == -1)
				{
					if (gameBoard[i][j + 3] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i][j + 3] = "��";
						return 0;
					}
				}
				else if (j + 3 == BOARD_SIZE)
				{
					if (gameBoard[i][j - 1] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i][j - 1] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i][j - 1] == "��" && gameBoard[i][j + 3] == "��") {}

				//���� 3���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i][j - 1] == "��")
				{
					gameBoard[i][j + 3] = "��";
					return 0;
				}
				else if (gameBoard[i][j + 3] == "��")
				{
					gameBoard[i][j - 1] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					//[i][j - 1]�� ����ġ�� �� Ŭ ���
					if (weight[i][j - 1] > weight[i][j + 3])
					{
						gameBoard[i][j - 1] = "��";
						return 0;
					}

					//[i][j + 3]�� ����ġ�� �� Ŭ ���
					else if (weight[i][j - 1] < weight[i][j + 3])
					{
						gameBoard[i][j + 3] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * i + j - 1;
						saveweight[1] = 100 * i + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
						return 0;
					}
				}
			}
		}
	}

	//���η� 3���� ���
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��")
			{
				//���� 3���� ���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (i - 1 == -1)
				{
					if (gameBoard[i + 3][j] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i + 3][j] = "��";
						return 0;
					}
				}
				else if (i + 3 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i - 1][j] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i - 1][j] == "��" && gameBoard[i + 3][j] == "��") {}

				//���� 3���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i - 1][j] == "��")
				{
					gameBoard[i + 3][j] = "��";
					return 0;
				}
				else if (gameBoard[i + 3][j] == "��")
				{
					gameBoard[i - 1][j] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					//[i - 1][j]�� ����ġ�� �� Ŭ ���
					if (weight[i - 1][j] > weight[i + 3][j])
					{
						gameBoard[i - 1][j] = "��";
						return 0;
					}

					//[i + 3][j]�� ����ġ�� �� Ŭ ���
					else if (weight[i - 1][j] < weight[i + 3][j])
					{
						gameBoard[i + 3][j] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * (i - 1) + j;
						saveweight[1] = 100 * (i + 3) + j;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
						return 0;
					}
				}
			}
		}
	}

	//�밢�� �Ʒ��� 3���� ���
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��")
			{
				//���� 3���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (i - 1 == -1 || j - 1 == -1)
				{
					if (gameBoard[i + 3][j + 3] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i + 3][j + 3] = "��";
						return 0;
					}
				}
				else if (i + 3 == BOARD_SIZE || j + 3 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j - 1] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i - 1][j - 1] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i - 1][j - 1] == "��" && gameBoard[i + 3][j + 3] == "��") {}

				//���� 3���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i - 1][j - 1] == "��")
				{
					gameBoard[i + 3][j + 3] = "��";
					return 0;
				}
				else if (gameBoard[i + 3][j + 3] == "��")
				{
					gameBoard[i - 1][j - 1] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					//[i - 1][j - 1]�� ����ġ�� �� Ŭ ���
					if (weight[i - 1][j - 1] > weight[i + 3][j + 3])
					{
						gameBoard[i - 1][j - 1] = "��";
						return 0;
					}

					//[i + 3][j + 3]�� ����ġ�� �� Ŭ ���
					else if (weight[i - 1][j - 1] < weight[i + 3][j + 3])
					{
						gameBoard[i + 3][j + 3] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * (i - 1) + j - 1;
						saveweight[1] = 100 * (i + 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
						return 0;
					}
				}
			}
		}
	}

	//�밢�� ���� 3���� ���
	for (int i = 2; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��")
			{
				//���� 2���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (i - 3 == -1 || j + 3 == BOARD_SIZE)
				{
					if (gameBoard[i + 1][j - 1] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i + 1][j - 1] = "��";
						return 0;
					}
				}
				else if (i + 1 == BOARD_SIZE || j - 1 == -1)
				{
					if (gameBoard[i - 3][j + 3] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i - 3][j + 3] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i + 1][j - 1] == "��" && gameBoard[i - 3][j + 3] == "��") {}

				//���� 2���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i + 1][j - 1] == "��")
				{
					gameBoard[i - 3][j + 3] = "��";
					return 0;
				}
				else if (gameBoard[i - 3][j + 3] == "��")
				{
					gameBoard[i + 1][j - 1] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					//[i + 1][j - 1]�� ����ġ�� �� Ŭ ���
					if (weight[i + 1][j - 1] > weight[i - 3][j + 3])
					{
						gameBoard[i + 1][j - 1] = "��";
						return 0;
					}

					//[i - 3][j + 3]�� ����ġ�� �� Ŭ ���
					else if (weight[i + 1][j - 1] < weight[i - 3][j + 3])
					{
						gameBoard[i - 3][j + 3] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * (i + 1) + j - 1;
						saveweight[1] = 100 * (i - 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
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
	//���η� 4���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��")
			{
				//���� 4���� ���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (j - 1 == -1)
				{
					if (gameBoard[i][j + 4] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i][j + 4] = "��";
						return 0;
					}
				}
				else if (j - 1 == BOARD_SIZE)
				{
					if (gameBoard[i][j + 4] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i][j + 4] = "��";
						return 0;
					}
				}

				//���� 4���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i][j - 1] == "��" && gameBoard[i][j + 4] == "��") {}

				//���� 4���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i][j - 1] == "��")
				{
					gameBoard[i][j + 4] = "��";
					return 0;
				}
				else if (gameBoard[i][j + 4] == "��")
				{
					gameBoard[i][j - 1] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					saveweight[0] = 100 * i + j - 1;
					saveweight[1] = 100 * i + j + 4;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}
		}
	}

	//���η� 4���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��")
			{
				//���� 4���� ���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (i - 1 == -1)
				{
					if (gameBoard[i + 4][j] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i + 4][j] = "��";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i - 1][j] = "��";
						return 0;
					}
				}

				//���� 4���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i - 1][j] == "��" && gameBoard[i + 4][j] == "��") {}

				//���� 4���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i - 1][j] == "��")
				{
					gameBoard[i + 4][j] = "��";
					return 0;
				}
				else if (gameBoard[i + 4][j] == "��")
				{
					gameBoard[i - 1][j] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					saveweight[0] = 100 * (i - 1) + j;
					saveweight[1] = 100 * (i + 4) + j;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}
		}
	}

	//�밢�� �Ʒ��� 4���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��")
			{
				//���� 4���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (i - 1 == -1 || j - 1 == -1)
				{
					if (gameBoard[i + 4][j + 4] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i + 4][j + 4] = "��";
						return 0;
					}
				}
				else if (i + 4 == BOARD_SIZE || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i - 1][j - 1] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i - 1][j - 1] = "��";
						return 0;
					}
				}

				//���� 4���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i - 1][j - 1] == "��" && gameBoard[i + 4][j + 4] == "��") {}

				//���� 4���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i - 1][j - 1] == "��")
				{
					gameBoard[i + 4][j + 4] = "��";
					return 0;
				}
				else if (gameBoard[i + 4][j + 4] == "��")
				{
					gameBoard[i - 1][j - 1] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					saveweight[0] = 100 * (i - 1) + j - 1;
					saveweight[1] = 100 * (i + 4) + j + 4;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}
		}
	}

	//�밢�� ���� 4���� ���
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��")
			{
				//���� 4���� �� �� �� �� ���� ���� ���� ���� ���� ���
				if (i - 4 == -1 || j + 4 == BOARD_SIZE)
				{
					if (gameBoard[i + 1][j - 1] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i + 1][j - 1] = "��";
						return 0;
					}
				}
				else if (i + 1 == BOARD_SIZE || j - 1 == -1)
				{
					if (gameBoard[i - 4][j + 4] == "��") {}	//�� ���� �ϳ��� ��, �ϳ��� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.

					else
					{
						gameBoard[i - 4][j + 4] = "��";
						return 0;
					}
				}

				//���� 4���� ���� ���� ���� ������� ���� ���� ���� ���� ���, �ƹ��͵� ���� �ʴ´�.
				else if (gameBoard[i + 1][j - 1] == "��" && gameBoard[i - 4][j + 4] == "��") {}

				//���� 4���� ���� �� �� �� �� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i + 1][j - 1] == "��")
				{
					gameBoard[i - 4][j + 4] = "��";
					return 0;
				}
				else if (gameBoard[i - 4][j + 4] == "��")
				{
					gameBoard[i + 1][j - 1] = "��";
					return 0;
				}

				//���� ���� ���� ���
				else
				{
					saveweight[0] = 100 * (i + 1) + j - 1;
					saveweight[1] = 100 * (i - 4) + j + 4;

					srand(time(NULL));
					int random = rand() % 2;
					int b = saveweight[random] % 100;
					int a = (saveweight[random] - b) / 100;

					gameBoard[a][b] = "��";
					return 0;
				}
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk1_2s()
{
	//���η� 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��")
			{
				gameBoard[i][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "��")
			{
				gameBoard[i][j + 2] = "��";
				return 0;
			}
		}
	}

	//���η� 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��")
			{
				gameBoard[i + 1][j] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "��")
			{
				gameBoard[i + 2][j] = "��";
				return 0;
			}
		}
	}

	//������ �Ʒ� �밢������ 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 3; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��")
			{
				gameBoard[i + 1][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "��")
			{
				gameBoard[i + 2][j + 2] = "��";
				return 0;
			}
		}
	}

	//������ �� �밢������ 1 ��� 2���� �� Ȥ�� 2 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 3; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 3; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��")
			{
				gameBoard[i - 1][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "��")
			{
				gameBoard[i - 2][j + 2] = "��";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk1_3s()
{
	//���η� 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "+" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��" && gameBoard[i][j + 4] == "��")
			{
				gameBoard[i][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "+" && gameBoard[i][j + 4] == "��")
			{
				gameBoard[i][j + 3] = "��";
				return 0;
			}

			else {}
		}
	}

	//���η� 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��" && gameBoard[i + 4][j] == "��")
			{
				gameBoard[i + 1][j] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "+" && gameBoard[i + 4][j] == "��")
			{
				gameBoard[i + 3][j] = "��";
				return 0;
			}

			else {}
		}
	}

	//������ �Ʒ� �밢������ 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��" && gameBoard[i + 4][j + 4] == "��")
			{
				gameBoard[i + 1][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "+" && gameBoard[i + 4][j + 4] == "��")
			{
				gameBoard[i + 3][j + 3] = "��";
				return 0;
			}

			else {}
		}
	}

	//������ �� �밢������ 1 ��� 3���� �� Ȥ�� 3 ��� 1���� ���� ������ ���� ���� ���
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��" && gameBoard[i - 4][j + 4] == "��")
			{
				gameBoard[i - 1][j + 1] = "��";
				return 0;
			}

			else if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "+" && gameBoard[i - 4][j + 4] == "��")
			{
				gameBoard[i - 3][j + 3] = "��";
				return 0;
			}

			else {}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk2_2s()
{
	//���η� 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 3] == "��" && gameBoard[i][j + 4] == "��")
			{
				gameBoard[i][j + 2] = "��";
				return 0;
			}
		}
	}

	//���η� 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "+" && gameBoard[i + 3][j] == "��" && gameBoard[i + 4][j] == "��")
			{
				gameBoard[i + 2][j] = "��";
				return 0;
			}
		}
	}

	//������ �Ʒ� �밢������ 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "+" && gameBoard[i + 3][j + 3] == "��" && gameBoard[i + 4][j + 4] == "��")
			{
				gameBoard[i + 2][j + 2] = "��";
				return 0;
			}
		}
	}

	//������ �� �밢������ 2 ��� 2���� ���� ������ ���� ���� ���
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "+" && gameBoard[i - 3][j + 3] == "��" && gameBoard[i - 4][j + 4] == "��")
			{
				gameBoard[i - 2][j + 2] = "��";
				return 0;
			}
		}
	}

	return 0;
}

int Game_Board::cpu_chackshu_atk1_1s()
{
	//���η� 1 ��� 1���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 2] == "+" && gameBoard[i][j + 2] == "��")
			{
				//+��+��+�� ���, ������ Ȥ�� ���� +�� �����Ѵ�.
				if (gameBoard[i][j - 1] == "+" && gameBoard[i][j + 3] == "+")
				{
					//[i][j - 1]�� ����ġ�� �� Ŭ ���
					if (weight[i][j - 1] > weight[i][j + 3])
					{
						gameBoard[i][j - 1] = "��";
						return 0;
					}

					//[i][j + 3]�� ����ġ�� �� Ŭ ���
					else if (weight[i][j - 1] < weight[i][j + 3])
					{
						gameBoard[i][j + 3] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * i + j - 1;
						saveweight[1] = 100 * i + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i][j - 1] == "��" && gameBoard[i][j + 3] == "��") {}

				//���� ���� ���� ���� ���� ���� ���
				else if (j - 1 == -1 || j + 3 == BOARD_SIZE) {}

				//��+���� ���, ��� +�� �����Ѵ�.
				else
				{
					gameBoard[i][j + 1] = "��";
					return 0;
				}
			}
		}
	}

	//���η� 1 ��� 1���� ���
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "+" && gameBoard[i + 2][j] == "��")
			{
				//+��+��+�� ���, �� Ȥ�� �Ʒ� +�� �����Ѵ�.
				if (gameBoard[i - 1][j] == "+" && gameBoard[i + 3][j] == "+")
				{
					//[i - 1][j]�� ����ġ�� �� Ŭ ���
					if (weight[i - 1][j] > weight[i + 3][j])
					{
						gameBoard[i - 1][j] = "��";
						return 0;
					}

					//[i + 3][j]�� ����ġ�� �� Ŭ ���
					else if (weight[i - 1][j] < weight[i + 3][j])
					{
						gameBoard[i + 3][j] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * (i - 1) + j;
						saveweight[1] = 100 * (i + 3) + j;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i - 1][j] == "��" && gameBoard[i + 3][j] == "��") {}

				//���� ���� ���� ���� ���� ���� ���
				else if (i - 1 == -1 || i + 3 == BOARD_SIZE) {}

				//��+���� ���, ��� +�� �����Ѵ�.
				else
				{
					gameBoard[i + 1][j] = "��";
					return 0;
				}
			}
		}
	}

	//������ �Ʒ��� 1 ��� 1���� ���
	for (int i = 0; i < BOARD_SIZE - 2; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "+" && gameBoard[i + 2][j + 2] == "��")
			{
				//+��+��+�� ���, ������ �Ʒ� Ȥ�� ���� �� +�� �����Ѵ�.
				if (gameBoard[i - 1][j - 1] == "+" && gameBoard[i + 3][j + 3] == "+")
				{
					//[i - 1][j - 1]�� ����ġ�� �� Ŭ ���
					if (weight[i - 1][j - 1] > weight[i + 3][j + 3])
					{
						gameBoard[i - 1][j - 1] = "��";
						return 0;
					}

					//[i + 3][j + 3]�� ����ġ�� �� Ŭ ���
					else if (weight[i - 1][j - 1] < weight[i + 3][j + 3])
					{
						gameBoard[i + 3][j + 3] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * (i - 1) + j - 1;
						saveweight[1] = 100 * (i + 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i - 1][j - 1] == "��" && gameBoard[i + 3][j + 3] == "��") {}

				//���� ���� ���� ���� ���� ���� ���
				else if (i - 1 == -1 || j - 1 == -1 || i + 3 == BOARD_SIZE || j + 3 == BOARD_SIZE) {}

				//��+���� ���, ��� +�� �����Ѵ�.
				else
				{
					gameBoard[i + 1][j + 1] = "��";
					return 0;
				}
			}
		}
	}

	//������ ���� 1 ��� 1���� ���
	for (int i = 2; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 2; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "+" && gameBoard[i - 2][j + 2] == "��")
			{
				//+��+��+�� ���, ������ �� Ȥ�� ���� �Ʒ� +�� �����Ѵ�.
				if (gameBoard[i + 1][j - 1] == "+" && gameBoard[i - 3][j + 3] == "+")
				{
					//[i + 1][j - 1]�� ����ġ�� �� Ŭ ���
					if (weight[i + 1][j - 1] > weight[i - 3][j + 3])
					{
						gameBoard[i + 1][j - 1] = "��";
						return 0;
					}

					//[i - 3][j + 3]�� ����ġ�� �� Ŭ ���
					else if (weight[i + 1][j - 1] < weight[i - 3][j + 3])
					{
						gameBoard[i - 3][j + 3] = "��";
						return 0;
					}

					//�� ����ġ�� ���� ���
					else
					{
						saveweight[0] = 100 * (i + 1) + j - 1;
						saveweight[1] = 100 * (i - 3) + j + 3;

						srand(time(NULL));
						int random = rand() % 2;
						int b = saveweight[random] % 100;
						int a = (saveweight[random] - b) / 100;

						gameBoard[a][b] = "��";
						return 0;
					}
				}

				//���� 3���� ���� ���� ���� ������� ���� ���� ���� ���� ���
				else if (gameBoard[i + 1][j - 1] == "��" && gameBoard[i - 3][j + 3] == "��") {}

				//���� ���� ���� ���� ���� ���� ���
				else if (i - 3 == -1 || j - 1 == -1 || i + 1 == BOARD_SIZE || j + 3 == BOARD_SIZE) {}

				//��+���� ���, ��� +�� �����Ѵ�.
				else
				{
					gameBoard[i - 1][j + 1] = "��";
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
			if (gameBoard[i][j] == "��")
				count++;
		}
	}

	return count;
}

bool Game_Board::win_player()
{
	//���η� 5���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��" && gameBoard[i][j + 4] == "��")
				return 1;
		}
	}

	//���η� 5���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��" && gameBoard[i + 4][j] == "��")
				return 1;
		}
	}

	//������ �Ʒ� �밢������ 5���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��" && gameBoard[i + 4][j + 4] == "��")
				return 1;
		}
	}

	//������ �� �밢������ 5���� ���
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��" && gameBoard[i - 4][j + 4] == "��")
				return 1;
		}
	}

	return 0;
}

bool Game_Board::win_cpu()
{
	//���η� 5���� ���
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i][j + 1] == "��" && gameBoard[i][j + 2] == "��" && gameBoard[i][j + 3] == "��" && gameBoard[i][j + 4] == "��")
				return 1;
		}
	}

	//���η� 5���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j] == "��" && gameBoard[i + 2][j] == "��" && gameBoard[i + 3][j] == "��" && gameBoard[i + 4][j] == "��")
				return 1;
		}
	}

	//������ �Ʒ� �밢������ 5���� ���
	for (int i = 0; i < BOARD_SIZE - 4; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i + 1][j + 1] == "��" && gameBoard[i + 2][j + 2] == "��" && gameBoard[i + 3][j + 3] == "��" && gameBoard[i + 4][j + 4] == "��")
				return 1;
		}
	}

	//������ �� �밢������ 5���� ���
	for (int i = 4; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE - 4; j++)
		{
			if (gameBoard[i][j] == "��" && gameBoard[i - 1][j + 1] == "��" && gameBoard[i - 2][j + 2] == "��" && gameBoard[i - 3][j + 3] == "��" && gameBoard[i - 4][j + 4] == "��")
				return 1;
		}
	}

	return 0;
}

int main()
{
	Game_Board omok;

	int count_playerstone = 0;	//������� ���� ����

	while (true)
	{
		omok.printGB();		//�������� ǥ��
		omok.resetw();		//����ġ �ʱ�ȭ
		omok.resets();		//saveweight[]�ʱ�ȭ

		if (omok.win_cpu() == 1)	//��ǻ���� ���� ���� �̻��̶��
		{
			cout << endl << "����� �й��Դϴ�." << endl;
			break;
		}

		omok.player_chakshu();	//����� ����
		count_playerstone++;	//������� �� ���� ����
		omok.weighting();		//����ġ �ο�

		if (omok.win_player() == 1)	//������� ���� ���� �̻��̶��
		{
			omok.printGB();
			cout << endl << "�����մϴ�!" << endl << "����� �¸��Դϴ�." << endl;
			break;
		}

		//�ڱ� ���ʿ� �ڽ��� ���� 5���� �ȴٸ� �����Ѵ�.
		omok.cpu_chackshu_atk1_3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk2_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk4s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//���� ���ʿ� ��밡 5���� �Ǹ� ���´�.
		omok.cpu_chackshu_def4s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_def1_3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_def2_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//���� ���ʿ� ��밡 4���� �Ǹ� ���´�.
		omok.cpu_chackshu_def1_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//�ڱ� ���ʿ� �ڽ��� ���� 4���� �ȴٸ� �����Ѵ�.
		omok.cpu_chackshu_atk1_2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//�� �� ���� ���� 3���� ������ ���´�.
		omok.cpu_chackshu_def3s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//����� ���� ���ٸ� 2���� ���� 3���� ����� �����Ѵ�.
		omok.cpu_chackshu_atk1_1s();
		if (omok.count_cpustone() == count_playerstone)
			continue;
		omok.cpu_chackshu_atk2s();
		if (omok.count_cpustone() == count_playerstone)
			continue;

		//���� �ش������ ���ٸ� ����ġ�� ���� �����Ѵ�.
		omok.cpu_chakshu_weight();
		if (omok.count_cpustone() == count_playerstone)
			continue;
	}

	return 0;
}