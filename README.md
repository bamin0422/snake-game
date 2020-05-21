# snake-game

C++ 프로그래밍 언어로 ncurses 라이브러리를 사용하여 Snake Game 을 구현한다. snake-game은 1~5단계 안에 있는 game-rule을 걸쳐 프로그램이 실행된다. 

<br>

![](/img/snake-game.png)

다음은 **snake-game의 구조**이다.

- Snake Body : Head는 플레이되는 본체, 방향키를 사용해 움직일 수 있다.
- Growth Item : 획득 시, Body의 길이가 1 증가한다.
- Poison Item : 획득 시, Body의 길이가 1 감소, 길이가 3보다 작아지면 게임 종료.
- Gate A, B : 한 쪽 Gate에 들어가면 다른 쪽 Gate로 나오는 구조, 임의의 벽에서만 생성한다.
- Wall : Gate로 변할 수 있지만, Wall인 상태에서는 Snake가 통과할 수 없다. Snake Head와 충돌 시 게임이 종료된다.
- Immune Wall : Wall이 꺾이는 위치에 존재한다. Gate로 변할 수 없고, Snake가 통과할 수 없다. Snake Head와 충돌 시 게임이 종료된다.
- Score Board : Snake Boddy의 길이를 (현재길이) / (최대길이) 형태로 표시하고, 각각의 획득한 Item 갯수와, Gate 사용 횟수를 출력한다.
- Mission :  Snake Boddy의 길이와, 획득할 Item의 갯수, Gate 사용 횟수의 목표치와 달성 여부를 출력한다. 목표 달성 시 게임이 종료된다.

<br>

<br>

## **1단계** 

- NCurses Library 함수들을 사용해 Snake Map을 Game 화면에 출력.
- Wall은 **흰색 네모**, Immune Wall은 **회색 네모**로 윈도우에 출력.

<br>

## 2단계

- Map 위에 Snake를 표시하고, 화살표를 입력받아 Snake가 0.5초당 1의 거리가 움직이도록 프로그램을 완성한다.
- Snake의 출력은 Head는 **주황색 네모**, Body는 **노란색 네모**로 출력한다. 
- Snake는 입력된 방향키로 이동하되, 진행방향의 반대방향으로 이동할 수 없다.
  - Head가 진행방향
  - Tail 방향으로 이동할 수 없다. 이동 시 Game Over.
- 다른 실패 조건
  - 자신의 Body에 닿거나, Gate가 아닌 Wall에 충돌 시 Game Over.

<br>

## 3단계

- 2단계 프로그램에서, Map 위에 Growth Item과 Poison Item을 출현하도록 수정.
- Growth Item은 **초록색 네모**, Poison Item은 **빨간색 네모**로 출력한다.
- Growth Item
  - 획득 시, 몸의 길이가 1만큼 증가한다.
  - 몸의 길이는 진행방향으로 증가한다.
- Poison Item
  - 획득 시, 몸의 길이가 1만큼 꼬리 부분이 감소한다.
  - Poison  Item을 획득 해, 길이가 3이하가 됐을 경우 Game Over된다.
- Growth Item과 Poison Item의 출현
  - Snake Body, Wall이 있지 않은 임의의 Map 안에 출현하도록 한다.
  - 출현 후, 일정 시간(5초)이 지나면 사라지고, 다른 위치에 출현하도록 한다.
  - 동시에 출현할 수 있는 Item의 수는 3개로 제한한다.

<br>

## 4단계

- 3단계 프로그램에서, Map에 존재하는 Wall의 임의의 위치에 한 쌍의 Gate가 출현할 수 있도록 변경하고, 각 Gate에 Snake가 통과할 수 있도록 수정한다.

- Gate의 출현 방법

  - 게임 시작 후, Snake Body가 7을 초과할 경우 발생.
  - 10초마다 위치가 변경, Snake가 Gate를 통과 했을 경우 위치 변경.

- Gate

  - 두 개가 한 쌍이고, 한 번에 한 쌍만 나타난다.
  - 겹치지 않는다.
  - Snake가 진입하면, 다른 Gate로 진출한다.
  - 진입 중인 경우, Gate는 사라지거나 다른 위치에 나타나지 않는다.

- Gate가 나타나는 벽이 가장자리에 있을 경우.

  - 항상 Map의 안쪽 방향으로 진출한다.

    | 벽의 위치 | 진행 방향   |
    | --------- | ----------- |
    | 상단      | 아래 방향   |
    | 하단      | 위 방향     |
    | 좌측      | 오른쪽 방향 |
    | 우측      | 왼쪽 방향   |

- Gate가 나타나는 벽이 Map의 안쪽에 위치할 경우.

  - 진입방향과 일치하는 방향이 우선

  - 진출 방향이 좌-우인 경우

    | 진입 방향   | 진출 방향   |
    | ----------- | ----------- |
    | 위 방향     | 왼쪽 방향   |
    | 아래 방향   | 왼쪽 방향   |
    | 오른쪽 방향 | 오른쪽 방향 |
    | 왼쪽 방향   | 왼쪽 방향   |

  - 진출 방향이 상-하인 경우

    | 진입 방향   | 진출 방향 |
    | ----------- | --------- |
    | 오른쪽 방향 | 위 방향   |
    | 위쪽 방향   | 위 방향   |
    | 왼쪽 방향   | 아래 방향 |
    | 아래 방향   | 아래 방향 |

- Wall

  - Gate로 변할 수 있다.
  - Snake가 통과할 수 없다, Snake Head와 충돌 시 Game Over된다.

- Immune Wall

  - Wall이 겹치는 곳에 위치한 Wall.
  - Gate로 변할 수 없다.

<br>

## 5단계

- 프로그램 우측에 게임 점수를 표시하는  Score Board를 구성한다.
- Score Board 아래에 Mission을 구성한다.
- Mission을 달성하면 다음 Map으로 진행하도록 프로그램을 완성한다.
- ScoreBoard 구성
  - B: (현재 길이)/(최대 길이)
  - G : (획득한 Growth Item의 수)
  - P : (획득한 Poison Item의 수)
  - g : (Gate 사용 횟수)
- Mission 구성
  - B : 10 (목표달성여부)
  - G : 7   (V)
  - P : 3   (   )
  - g : 1   (   )

=======

C++ 프로그래밍 언어로 ncurses 라이브러리를 사용하여 Snake Game 을 구현한다.

# snake-game 기능 구현

#
>>>>>>> c260f0b1c27742bb6b35b5532209c3978f29adf0
