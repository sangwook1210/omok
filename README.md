# omok

● 프로그램 설계 / 알고리즘
0) Game_Board 클래스가 있다.
 `string gameBoard[BOARD_SIZE][BOARD_SIZE];`로 돌이 놓일 칸들을 선언한다.
이 클래스의 생성자는 모든 gameboard[][]를 “+”로 초기화한다.

1) 게임판의 상황을 표시해주는 printGB()멤버 함수는 BOARD_SIZE가 짝수일 때와, 홀수일 때를 구분하여 크기를 알맞게 조정하여 출력한다. 빈 칸은 +로, 사용자가 둔 돌은 ●로, 컴퓨터가 둔 돌은 ○로 표기한다.

2) 사람이 착수하는 player_chackshu()멤버 함수는 while(true) 안에 가로와 세로 값을 입력받고 
if (gameBoard[inputcol][inputrow] == "●" || gameBoard[inputcol][inputrow] == "○")<br>
//놀 자리에 돌이 있을 경우 continue;<br>
else if (inputcol >= 19 || inputcol < 0 || inputrow >= 19 || inputcol < 0)<br>
//입력받은 좌표가 게임판 밖일 경우 continue;<br>
else break;<br>
로 알맞은 좌표를 입력받을 때까지 반복한 다음 알맞은 좌표(else)가 나왔을 경우. 
gameBoard[inputcol][inputrow] = "●";로 흑돌을 착수한다.

3) 플레이어의 승리를 판단하는 `bool win_player()`멤버 함수가 있다.
이 함수는 2중 for문으로 모든 칸을 검사하여 5개의 연속된 ●가 있으면 1을 return하고 문구를 출력하고 프로그램을 종료한다. 돌이 나열되는 방법은 가로, 세로, 오른쪽 아래 대각선, 오른쪽 위 대각선으로 총 4가지의 경우가 있는데, 이를 검사하는 방법은 컴퓨터가 공격하거나 방어하는데 쓰는 방법과 같기 때문에 밑에서 설명하겠다.

4) 가중치를 부여하기 위하여 `int weight[BOARD_SIZE][BOARD_SIZE];`로 가중치가 들어갈 배열을 선언한다.
 resetw()라는 멤버 함수는 이중 for문을 이용하여 모든 weight[][]값을 0으로 초기화한다.
 가중치를 부여하는 `weighting()`이라는 멤버 함수는 이중 for문으로 게임판의 모든 점을 검사한다. `gameBoard[i][j] == "●"`라면, 주위 8돌의 `weight[][]`를 +2한다. `gameBoard[i][j] == "○"`라면, 주위 8돌의 `weight에[][]`를 –2한다. 가중치를 부여하는 이중 for문이 끝나면, 새로운 이중 for문을 선언한다. 이는 `gameBoard[i][j]`의 값이 ●혹은 ○라면, 그 `weight[i][j]`의 값을   –99로 만들어 가중치에 의해 착수할 때, 돌이 있는 자리에는 착수하지 못하게 하는 역할을 한다.

5) 컴퓨터가 착수할 수 있는 경우<br>
<img width="1318" alt="1" src="https://user-images.githubusercontent.com/112921582/221409206-2ad56c37-5704-477a-9542-3be307903e0b.png"><br>
`cpu_chakshu_weight()`는 가중치를 이용하여 컴퓨터가 착수하는 것이다.
`cpu_chakshu_def~()`는 ~의 상황이 왔을 때 컴퓨터가 방어적인 수를 두는 것이다.
`cpu_chackshu_atk~(`)는 컴퓨터가 방어할 필요가 없을 경우, ~의 상황에서 공격적인 수를 두는 것이다.
그리고 숫자 뒤의 s는 stone을 의미한다. 예를 들어 4s이면 4개의 돌이 연속적인 상황이고, 1_2s이면 1 띄고 2 혹은 2 띄고 1개의 돌이 연속적인 상황이다.

 3)의 방법을 포함한 이러한 컴퓨터가 착수하는 수들은 기본적인 로직이 거의 비슷하다. 이들 중 대표적인 로직을 하나만 소개하고, 나머지는 소스코드의 주석에 상세하게 적어 놨으므로 이를 확인하면 된다.

우선 빈칸을 포함한 나열된 돌들의 총 개수를 세야 한다. 4s면 4, 3s면 3, 1_2s면 4, 2_2s면 5 이런 식으로 말이다. 그리고 그 값에서 1을 뺀 값을 a라 하자.





i) 돌들이 가로로 나열된 경우<br>
for (int i = 0; i < BOARD_SIZE; i++)<br>
{<br>
  for (int j = 0; j < BOARD_SIZE - a; j++)<br>
	{<br>
	}<br>
}<br>
의 형식으로 이중 for문을 작성한다.

ii) 돌들이 세로로 나열된 경우<br>
for (int i = 0; i < BOARD_SIZE - a; i++)<br>
{<br>
	for (int j = 0; j < BOARD_SIZE; j++)<br>
	{<br>
	}<br>
}<br>
의 형식으로 이중 for문을 작성한다.

iii) 돌들이 오른쪽 아래 대각선으로 나열된 경우<br>
for (int i = 0; i < BOARD_SIZE - a; i++)<br>
{<br>
	for (int j = 0; j < BOARD_SIZE - a; j++)<br>
	{<br>
	}<br>
}<br>
의 형식으로 이중 for문을 작성한다.

iv) 돌들이 오른쪽 위 대각선으로 나열된 경우<br>
for (int i = a; i < BOARD_SIZE; i++)<br>
{<br>
	for (int j = 0; j < BOARD_SIZE - a; j++)<br>
	{<br>
	}<br>
}<br>
의 형식으로 이중 for문을 작성한다.

안의 세부적인 내용들을 간단하게 살펴보면
 def3s는 3개의 돌의 끝 중 한 쪽 끝이 판의 끝에 막혀 있다면 굳이 막을 필요가 없다.
만약 3개의 돌의 끝 중 한 쪽 끝이 이미 컴퓨터의 돌로 막혀 있다면 굳이 막을 필요가 없다.
막혀 있지 않을 경우 두 끝 중 한 쪽에 무작위로 착수한다.
의 로직으로 구성되어 있다. 여기서 무작위로 착수하는 것은 chackshu_weight()쪽에서 상세하게 다룰 것이다.

 def4s는 4개의 돌의 한 쪽 끝이 벽에 막혀 있다면 다른 한 쪽만 막으면 된다.
4개의 돌의 한 쪽 끝이 컴퓨터의 돌로 막혀 있다면 다른 한 쪽만 막으면 된다.
둘 다 아니라면 넘어간다.
의 로직으로 구성되어 있다.

def1_2s는 만약 1 띄고 2개의 돌의 끝 중 하나가 막혀 있으면 굳이 막을 필요가 없다.
그게 아니라면 뚫린 곳을 막는다.
의 로직으로 구성되어 있다. 

그리고 모든 cpu_chackshu들은 int 함수로 돌을 착수한 순간 return 0;로 함수를 끝내도록 설계되어 있다.

이 외의 def와 atk들의 상세한 로직은 소스코드의 주석에 적혀 있다.

이제 가중치에 의해 착수하는 chackshu_weight()에 대하여 알아보자. 
초기의 max값을 weight[0][0]로 선언한다.
count=0이다.<br><br>

for (int i = 0; i < BOARD_SIZE; i++)<br>
{<br>
	for (int j = 0; j < BOARD_SIZE - 1; j++)<br>
	{<br>
	if (max < weight[i][j + 1])<br>
		max = weight[i][j + 1];<br>
	}<br>
}<br>
의 이중 for문으로 모든 weight값들을 비교하여 가중치들 중 가장 큰 값이 max가 되도록 한다.<br>

for (int i = 0; i < BOARD_SIZE; i++)<br>
{<br>
	for (int j = 0; j < BOARD_SIZE - 1; j++)<br>
	{<br>
		if (max == weight[i][j])<br>
		{<br>
			saveweight[count] = 100 * i + j;	<br>
			count++;	<br>
		}<br>
	}	<br>
}<br>
이중 for문을 돌린다. 만약 max값과 weight[i][j]값이 같다면, int saveweight[count] 배열에 i와 j를 천과 백의 자리는 i, 십과 일의 자리는 j의 네자리 수의 형식으로 저장한다. 그리고 count++로 saveweight[]의 다음 칸에 다음 weight[i][j]가 저장될 수 있도록 한다.<br>
이제 count의 개수가 가장 큰 가중치들의 개수이다. <br><br>

srand(time(NULL));<br>
int random=rand()%count;<br>
로 0에서부터 count-1 중 하나를 랜덤으로 뽑는다.<br><br>

int b = saveweight[random] % 100;<br>
int a = (saveweight[random] - b) / 100;	<br>
로 합체해놨던 가중치의 좌표를 다시 분해해<br>
gameBoard[a][b] = "○";<br>
로 그곳에 착수한다.<br><br>

위에서 말한 무작위로 두는 방법은 위의 과정에서 saveweight[count]가 saveweight[0] 과 saveweight[1]로 바뀌고 양 쪽 끝 중 하나에 무작위로 두면 되므로 2로 나눈 나머지를 rand()%2; 로 구한 것이다.<br><br>

그리고 마지막으로 위 예외들의 우선순위는<br>
cpu_chackshu_atk1_3s();<br>
cpu_chackshu_atk2_2s();<br>
cpu_chackshu_atk4s();<br>
자기 차례에 자신의 돌이 5개가 된다면 공격하고<br><br>

cpu_chackshu_def4s();<br>
cpu_chackshu_def1_3s();<br>
cpu_chackshu_def2_2s();<br>
다음 차례에 상대가 5개가 되면 막고<br><br>

cpu_chackshu_def1_2s();<br>
다음 차례에 상대가 4개가 되면 막는다.<br>

cpu_chackshu_atk1_2s();<br>
cpu_chackshu_atk3s();<br>
자기 차례에 자신의 돌이 4개가 된다면 공격하고<br><br>

cpu_chackshu_def3s();<br>
양 쪽 끝이 열린 3목이 있으면 막고<br><br>

cpu_chackshu_atk1_1s();<br>
cpu_chackshu_atk2s();<br>
방어할 게 없다면 2개의 돌을 3개로 만들어 공격하고<br><br>

cpu_chakshu_weight();<br>
그것도 없다면 가중치에 의해 착수한다.<br><br>

6) 5)에서 컴퓨터가 착수하고 win_cpu()함수에서 ○가 연속으로 5개 이상이 되는지 확인한다. 만약 그렇다면 1을 return하고 문구를 출력한 후 프로그램이 종료된다.<br><br>

7) 그렇지 않다면 continue;한다.<br><br>
