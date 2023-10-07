#include <stdio.h>
#pragma warning(disable : 4996)

/*//1-1

int* MAX(int ar[]);
int* MIN(int ar[]);

int main()
{
	int N; //입력될 줄 수에 해당하는 정수N
	int ar[100]; //한 줄의 값을 저장할 배열
	int* p; //반복문에 사용할 포인터 변수

	scanf("%d", &N); //N의 값을 입력받음
	for (int i = 0; i < N; i++) //N줄의 데이터를 입력받음
	{
		for (p = ar; p < ar + 100 ; p++) //ar에 한 줄의 데이터를 넣어야하므로 반복문 수행
		{
			scanf("%d", p);
			if (*p == 0) //값이 0이면 한 줄의 입력을 멈춘다
				break;
		}
		printf("%d %d\n", *MAX(ar), *MIN(ar)); //한줄의 최대 최소 출력
	}
}

int* MAX(int ar[])
{
	int* p = ar; //탐색에 사용할 포인터변수
	int* pmax = NULL; //최대값을 저장할 임시 포인터 변수
	int max = -2147483648; //최대값과 비교하기위해 int의 최소로 초기화한다
	for (p = ar; p < ar + 100; p++)
	{
		if (*p == 0) //0을 찾으면
			break; //탐색종료
		if (max < *p) //탐색중 기존 최대보다 큰 값을 찾으면
		{
			max = *p; //최대값갱신
			pmax = p; //최대인 위치의 주소 저장
		}
	}
	return (pmax); //최대인 위치의 주소 반환
}

int* MIN(int ar[])
{
	int* p = ar; //탐색에 사용할 포인터변수
	int* pmin = NULL;//최소값을 저장할 임시 포인터 변수
	int min = 2147483647;//최소값과 비교하기위해 int의 최대로 초기화한다
	for (p = ar; p < ar + 100; p++)
	{
		if (*p == 0) //0을 찾으면
			break; //탐색종료
		if (min > *p)//탐색중 기존 최대보다 작은 값을 찾으면
		{
			min = *p; //최소값갱신
			pmin = p;//최소인 위치의 주소 저장
		}
	}
	return (pmin);//최소인 위치의 주소 반환
}*/

/*//1-2
int* MAX(int ar[]);
int* MIN(int ar[]);

int main()
{
	int N; //입력될 줄 수에 해당하는 정수N
	int ar[100]; //한 줄의 값을 저장할 배열
	int* p; //반복문에 사용할 포인터 변수
	int* pmax, * pmin; //최대 최소의 주소를 저장할 변수

	scanf("%d", &N); //N의 값을 입력받음
	for (int i = 0; i < N; i++) //N줄의 데이터를 입력받음
	{
		for (p = ar;; p++) //ar에 한 줄의 데이터를 넣어야하므로 반복문 수행
		{
			scanf("%d", p);
			if (*p == 0) //값이 0이면 한 줄의 입력을 멈춘다
				break;
		}
		pmax = MAX(ar); //pmax에 최대인 부분의 주소를 저장
		pmin = MIN(ar); //pmin에 최소인 부분의 주소를 저장
		if (pmax == pmin + 1 || pmin == pmax + 1) //사이의 값이 없는경우
			printf("none");
		if (pmax > pmin) //pmax가 주소상에서 pmin보다 우측에 있으면
		{
			for (p = pmin + 1; p < pmax; p++) //p를 pmin으로 초기화하여 출력
				printf("%d ", *p);
		}
		else if (pmin > pmax) //pmax가 주소상에서 pmin보다 좌측에 있으면
		{
			for (p = pmax + 1; p < pmin; p++) //p를 pmax로 초기화하여 출력
				printf("%d ", *p);
		}
		else //주소가 같은 경우는 none출력
			printf("none");
		printf("\n"); //한줄마다 줄바꿈해주기
	}
}

int* MAX(int ar[])
{
	int* p = ar; //탐색에 사용할 포인터변수
	int* pmax = NULL; //최대값을 저장할 임시 포인터 변수
	int max = -2147483648; //최대값과 비교하기위해 int의 최소로 초기화한다
	for (p = ar; p < ar + 100; p++)
	{
		if (*p == 0) //0을 찾으면
			break; //탐색종료
		if (max < *p) //탐색중 기존 최대보다 큰 값을 찾으면
		{
			max = *p; //최대값갱신
			pmax = p; //최대인 위치의 주소 저장
		}
	}
	return (pmax); //최대인 위치의 주소 반환
}

int* MIN(int ar[])
{
	int* p = ar; //탐색에 사용할 포인터변수
	int* pmin = NULL;//최소값을 저장할 임시 포인터 변수
	int min = 2147483647;//최소값과 비교하기위해 int의 최대로 초기화한다
	for (p = ar; p < ar + 100; p++)
	{
		if (*p == 0) //0을 찾으면
			break; //탐색종료
		if (min > *p)//탐색중 기존 최대보다 작은 값을 찾으면
		{
			min = *p; //최소값갱신
			pmin = p;//최소인 위치의 주소 저장
		}
	}
	return (pmin);//최소인 위치의 주소 반환
}*/

/*//2-1
int main()
{
	int N;//승객의 수
	int ar[21]; //idx번 승색이 예약한 좌석번호를 저장할 배열
	int* p, *pp; //반복문으로 배열탐색에 사용할 포인터변수
	int cnt;//중복되서 나온 횟수를 셀 변수
	int mem[21] = {0}; //중복된 숫자를 저장할 배열
	int *pmem = mem; //mem위치저장에 사용할 포인터변수
	int flag = 0; //중복된숫자가 있으면 1로 초기화되는 플래그변수

	scanf("%d", &N); //승객수를 입력받음
	for (p = ar; p < ar + N; p++) //ar을 탐색한다
		scanf("%d", p); //ar에 각 승객이 예약한 좌석번호를 저장한다
	if (N < 5) //승객이 5명보다 적은경우
	{
		printf("-1\n"); //-1출력
		return (0); //main함수 종료
	}
	for (p = ar; p < ar + N; p++)
	{
		cnt = 1; //1으로 초기화한다
		for (pp = p + 1; pp < ar + N; pp++) //p의 위치부터 끝까지 탐색한다
		{
			if (*pp == *p) //중복숫자가 나오면
				cnt++; //카운트한다
		}
		if (cnt != 1) //중복된 값이 있으면
		{
			flag++; //중복을 찾으면 flag를 증가시킨다.
			for (pp = mem; pp < mem + 21; pp++) //중복된 숫자를 저장하는 배열을 탐색
			{
				if (*pp == *p) //중복된 값이 이미 배열에 있으면 출력하지 않는다
					break;
			}
			if (pp == mem + 21) //새로찾은 중복된 값이 배열에 없으면
			{
				*pmem = *p; //mem에 새로찾은 중복값 저장
				pmem++; //mem의 주소를 다음번으로 올려준다
				printf("%d %d\n", *p, cnt); //출력
			}
		}
	}
	if (!flag) //중복된 숫자가 없이 flag가 0이면
		printf("%d\n", flag); //0을 출력한다
}*/

/*//2-2
int passengerN(int n);
void	rebooking(int* ar);
int changeseat(int* ar);
int main()
{
	int N;//승객의 수
	int ar[21] = {0}; //idx번 승색이 예약한 좌석번호를 저장할 배열
	int* p; //반복문으로 배열탐색에 사용할 포인터변수

	scanf("%d", &N); //승객수를 입력받음
	for (p = ar; p < ar + N; p++) //ar을 탐색한다
		scanf("%d", p); //ar에 각 승객이 예약한 좌석번호를 저장한다
	if (passengerN(N) == -1) //승객이 5명보다 적은 경우
	{
		printf("-1\n"); //-1출력
		return (0); //종료한다
	}
	else //인원이 충분하면
		printf("0\n"); //0출력
	rebooking(ar); //중복된 예약좌석이 있다면 정정해준다
	for (p = ar; p < ar + N; p++) //ar을 탐색한다
		printf("%d ", *p); //예약좌석들 출력
}

int passengerN(int n) //승객수가 충분한지 판별하는 함수
{
	if (n < 5) //인원이 5보다 적으면
		return (-1); //-1반환
	return (0); //충분하면 0반환
}

void	rebooking(int* ar) //자리 재예약해주는 함수
{ 
	int* p, *pp; //배열탐색에 사용할 포인터변수
	for (p = ar; p < ar + 21; p++) //ar을 탐색할 p
	{
		for (pp = p + 1; pp < ar + 21; pp++) //pp로 p의 다음위치부터 ar을 탐색한다
		{
			if (*pp == *p) //중복값이 보이면
				*pp = changeseat(ar); //배열에 존재하지 않으면서 최소인 값으로 바꿔준다
		}
	}
}

int changeseat(int* ar)
{
	int* p; //배열을 탐색하기위한 포인터변수
	for (int i = 1; i <= 21; i++) //예약좌석은 1번부터 21번까지이므로
	{
		for (p = ar; p < ar + 21; p++) //p = ar로 탐색시작
		{
			if (*p == i) //i가 배열에 이미 존재하는 값이면
				break;
		}
		if (p == ar + 21) //i가 배열에 존재하지 않는 값이면
			return (i); //i를 반환한다
	}
}*/

/*//3-2
void	PRT(int n, char* p)
{
	while (n--)
	{
		printf("%c", *p++);
	}
}

int	main(void)
{
	char	input[101];
	char* p;
	char	*pmax, *temp;
	int		max = 0;
	int		i;

	scanf("%s", input);
	pmax = input;
	p = input;
	while (*p)
	{
		i = 0;
		temp = p;
		while (*p && *p >= 'a' && *p <= 'z' && *p != '#')
		{
			i++;
			p++;
		}
		if (max < i)
		{
			max = i;
			pmax = temp;
		}
		p++;
	}
	PRT(max, pmax);
}*/

/*//3-1
int main()
{
	char str[100] = {0}; //문자를 저장할 문자배열
	char* p; //배열을 탐색할때 사용할 포인터변수 
	char	ch; //문자하나를 입력받을 임시 문자열변수
	int max_len = -21474836, len = 0; //가장 긴 단어의 길이와 한 단어의 길이를 저장할변수

	for (p = str; p < str + 100; p++) //p로 str을 탐색한다
	{
		scanf("%c", &ch); //ch에 문자1개를 입력받는다
		*p = ch; //str에 문자를 넣어준다
		if (ch == '#') //문자가 #이면 입력종료이므로
			break; //반복문 종료
	}
	for (p = str; p < str + 100; p++) //p로 str을 훑어본다
	{
		if (*p >= 'a' && *p <= 'z') //현재문자가 소문자이면
		{
			len++; //길이를 증가시킨다
			printf("%c", *p); //단어에 속하므로 출력한다
			if ((*(p + 1) < 'a' || *(p + 1) > 'z')) //다음 단어가 문자가 아니면
			{
				printf("\n"); //단어의 끝이므로 개행
				if (max_len < len) //이번 단어의 길이가 기존의 최대보다 크면 
				{
					max_len = len; //길이를 갱신한다
				}
				len = 0; //단어가 끝났으므로 len을 0으로 초기화한다
			}
		}
		else if (*p == '#') //현재문자가 #이면
			break; //문자열의 끝이므로 반복문 종료
	}
	printf("%d", max_len); //가장 긴 단어의 길이를 출력한다
}*/

/*//3-2

void PRT(int n, char* p);

int main()
{
	char str[100] = { 0 }; //문자를 저장할 문자배열
	char* p; //배열을 탐색할때 사용할 포인터변수 
	char* max_p = str; //가장 긴 단어의 시작주소를 저장할 변수
	char	ch; //문자하나를 입력받을 임시 문자열변수
	int max_len = -21474836, len = 0; //가장 긴 단어의 길이와 한 단어의 길이를 저장할변수

	for (p = str; p < str + 100; p++) //p로 str을 탐색한다
	{
		scanf("%c", &ch); //ch에 문자1개를 입력받는다
		*p = ch; //str에 문자를 넣어준다
		if (ch == '#') //문자가 #이면 입력종료이므로
			break; //반복문 종료
	}
	for (p = str; p < str + 100; p++) //p로 str을 훑어본다
	{
		if (*p >= 'a' && *p <= 'z') //현재문자가 소문자이면
		{
			len++; //길이를 증가시킨다
			printf("%c", *p); //단어에 속하므로 출력한다
			if ((*(p + 1) < 'a' || *(p + 1) > 'z')) //다음 단어가 문자가 아니면
			{
				printf("\n"); //단어의 끝이므로 개행
				if (max_len < len) //이번 단어의 길이가 기존의 최대보다 크면 
				{
					max_p = p - len + 1; //현재주소로부터 가장 긴 단어의 시작주소를 역산
					max_len = len; //길이를 갱신한다
				}
				len = 0; //단어가 끝났으므로 len을 0으로 초기화한다
			}
		}
		else if (*p == '#') //현재문자가 #이면
			break; //문자열의 끝이므로 반복문 종료
	}
	printf("%d %c\n", max_len, *max_p); //가장 긴 단어의 길이와 시작문자를 출력한다
	PRT(max_len, max_p);
}

void PRT(int n, char* p)
{
	char* str; //p를 탐색할 char형 포인터

	for (str = p; str < p + n; str++) //시작지점부터 n개 훑어본다
		printf("%c", *str); //훑어본 문자 출력
}*/

/*//4-1
int main()
{
	int a[10], b[10]; //101호와 102호에서 시험본 학생의 점수를 저장할 배열
	int num; //배열에 넣기전 점수를 넣을 변수
	int* p; //배열을 훑는데 사용하는 변수 p
	int max, min;//전체의 최고점수와 최저점수를 저장할 변수
	int max_a = -1, max_b = -1; //101호와 102호의 학생중 최고득점자의 점수를 저장할 변수
	int min_a = 101, min_b = 101; //101호와 102호의 학생중 최저득점자의 점수를 저장할 변수
	int cnt_a = 0, cnt_b = 0; //101호와 102호의 학생수를 카운트할 변수

	for (p = a; p < a + 11; p++) //배열 a를 훑으면서 값을 입력받는다
	{
		cnt_a++; //101호의 학생수 + 1
		scanf("%d", &num); //정수를 입력받음
		if (num == -1) //입력받은 값이 -1이면
		{
			cnt_a--; //-1인원 제외
			break; //반복문종료
		}
		*p = num; //배열에 정수를 넣는다
		if (max_a < *p) //기존 최고득점이 입력받은 점수보다 낮으면
			max_a = *p; //최고득점갱신
		if (min_a > *p) //기존 최저득점이 입력받은 점수보다 높으면
			min_a = *p; //최저점갱신
	}
	for (p = b; p < b + 11; p++) //배열 b를 훑으면서 값을 입력받는다
	{
		cnt_b++; //102호의 학생수 + 1
		scanf("%d", &num); //정수를 입력받음
		if (num == -1) //입력받은 값이 -1이면
		{
			cnt_b--;//-1인원 제외
			break; //반복문종료
		}
		*p = num; //배열에 정수를 넣는다
		if (max_b < *p) //기존 최고득점이 입력받은 점수보다 낮으면
			max_b = *p; //최고득점갱신
		if (min_b > *p) //기존 최저득점이 입력받은 점수보다 높으면
			min_b = *p; //최저점갱신
	}
	max = (max_a > max_b) ? max_a : max_b; //max_a와 max_b중 큰것을 max에 저장
	min = (min_a < min_b) ? min_a : min_b; //min_a와 min_b중 작은것을 min에 저장
	printf("%d %d\n", cnt_a, cnt_b);//101호와 102호의 학생수출력
	printf("%d %d\n", max, min); //최고점 최저점 출력
}*/

/*//4-2
int main()
{
	int a[10], b[10]; //101호와 102호에서 시험본 학생의 점수를 저장할 배열
	int num; //배열에 넣기전 점수를 넣을 변수
	int* p, *q, *pp; //배열을 훑는데 사용하는 변수
	int cnt_a = 0, cnt_b = 0; //101호와 102호의 학생수를 카운트할 변수
	int tmp; //정렬중 저장할 임시변수

	for (p = a; p < a + 11; p++) //배열 a를 훑으면서 값을 입력받는다
	{
		cnt_a++; //101호의 학생수 + 1
		scanf("%d", &num); //정수를 입력받음
		if (num == -1) //입력받은 값이 -1이면
		{
			cnt_a--; //-1인원 제외
			break; //반복문종료
		}
		*p = num; //배열에 정수를 넣는다
	}
	for (p = b; p < b + 11; p++) //배열 b를 훑으면서 값을 입력받는다
	{
		cnt_b++; //102호의 학생수 + 1
		scanf("%d", &num); //정수를 입력받음
		if (num == -1) //입력받은 값이 -1이면
		{
			cnt_b--;//-1인원 제외
			break; //반복문종료
		}
		*p = num; //배열에 정수를 넣는다
	}
	//버블소트는 가장 큰 값을 찾고 n -1 범위에서 두번쨰로 큰 값을 찾는 방식으로 동작한다
	for (p = a + cnt_a - 1; p > a; p--) //첫 for문은 배열에서 정렬의 탐색범위를 제한한다 -> p가 배열의 마지막원소를 가리키게 만들고 p를 감소시켜 가장 큰 원소를 배열의 마지막에 저장한다
	{
		for (q = a; q < p ; q++) //두번째 for문은 배열의 첫원소부터 첫for문에서 정한 범위까지 비교해가며 가장 큰 값을 찾아나간다
		{
			if (*q > *(q + 1)) //두 원소를 비교해서 오름차순이 되도록 정렬한다
			{
				tmp = *q; //임시변수에 현재 값 저장
				*q = *(q + 1); //현재값에 다음 원소의 값 저장
				*(q + 1) = tmp; //다음 원소의 값에 임시변수에 넣어둔값저장
			}
		}
	}
	for (p = b + cnt_b - 1; p > b ; p--) //첫for문은 배열에서 탐색할 범위를 제한해주는 역할을 한다 -> p가 배열의 마지막원소부터 감소하여 첫 원소에 도달한다
	{
		for (q = b; q < p; q++) //두번쨰 for문은 배열을 순회하며 첫 for문에서 제한한 범위까지 정렬을 수행한다
		{
			if (*q > *(q + 1)) //두 원소를 비교해서 오름차순이 되도록 정렬한다
			{
				tmp = *q; //임시변수에 현재 값 저장
				*q = *(q + 1); //현재값에 다음 원소의 값 저장
				*(q + 1) = tmp; //다음 원소의 값에 임시변수에 넣어둔값저장
			}
		}
	}
	p = a + cnt_a - 1; //p에 a의 마지막 원소의 주소저장
	q = b + cnt_b - 1; //q에 b의 마자막 원소의 주소 저장
	for (pp = a + cnt_a; pp > a; pp--) //반복문으로 배열을 훑기위해 pp를 이용해서 cnt_a번 탐색한다
	{
		if (q >= b + cnt_b) //b배열의 모든 원소가 출력되어 a의 원소만 출력해야하는경우
		{
			printf("%d ", *p); //a의 원소출력
			p--; //주소값감소
			continue; //아래의 문장을 수행하지않고 현재 if문만 반복적으로 수행하게 만든다
		}
		if (*p > *q) //a배열의 현재값이 b배열의 값보다 더 크면
		{
			printf("%d ", *p); //a배열의 현재값출력
			p--; //주소값 감소
		}
		else //b배열의 현재값이 a배열보다 더 크면
		{
			printf("%d ", *q); //b배열의 현재값 출력
			q--; //주소값감소
		}
	}
	printf("\n");//줄바꿈
	p = a; //p를 a의 시작주소로
	q = b; //q를 b의 시작주소로
	for (pp = b; pp < b + cnt_b ; pp++)//반복문으로 배열을 훑기위해 pp를 이용해서 cnt_b번 탐색한다
	{
		if (p >= a + cnt_a) //a배열의 모든 원소가 출력되어 b의 원소만 출력해야하는경우
		{
			printf("%d ", *q); //b의 원소출력
			q++; //주소증가
			continue; //아래의 문장을 수행하지않고 현재 if문만 반복적으로 수행하게 만든다
		}
		if (*p < *q)//a배열의 현재값이 b배열의 값보다 더 작으면
		{
			printf("%d ", *p); //a배열의 현재값 출력
			p++;//주소값 감소
		}
		else//b배열의 현재값이 a배열보다 더 작으면
		{
			printf("%d ", *q);//b배열의 현재값 출력
			q++; //주소증가
		}
	}
}*/

/*
10 20 40 5 10 -1
100 100 50 20 5 90 80 75 75 60 -1
*/