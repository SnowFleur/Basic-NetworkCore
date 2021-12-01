# Basic-SnowNetCore SINCE 2021

### 환경 및 사용한 툴, 언어
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)
![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)
- C++17, X64

### 목적
- 네트워크 테스트를 위해 Code를 반복 제작하는 것을 방지하기 위해 만든 공개용 IOCP Server Library
- Send 와 Recv가 가능할 정도의 정말 단순한 기능만 지원을 한다.


### ❗️ 유의 사항
- 그냥 간단하게 로컬에서 테스트만 하기 위해서 제작했음
- 버퍼 관리, 스레드 관리 기능등은 넣지 않았음
- TCP/IP 프로토콜에서 발생할 수 있는 문제 또한 모든 부분을 상정하지는 않음
- 버그가 있을 수 있음
- 급하게 작성했기 때문에 추후 구조의 변화 및 Source Code 변화가 있을 수 있음
- 만약 사용하실 경우 참고만....


### 🔨 업데이트 예정 
- 다양한 C++17기능 (std::stirng_view, std::any, Fold Expression)
- Smart Pointer 도입 고려
- PacketHandler
- SQL Server 와 커넥트가능 하게
- Socket Pool
- Thread Safe Queue

### ✅ 업데이트 완료
 - Log Class 추가 (C++17: Fold Expression)
 - NetAddress Class 추가
 - Protocol Buffer 기반 테스트 프로젝트
 - IOCP 기반 Server lib
 - Lock Guard

### 📚 주요 클래스 설명 및 기능

#### CSnowSocket Class
- 기존 WinSocket을 Class 형태로 감싼 클래스로 Socket의 여러 기능을 사용할 수 있다.

#### CSnowSession Class
- 실제로 네트워크 통신을 진행할 Session Class로 CSnowSocket을 상속받고 있으며 Send, Recv, Bind 등의 기능을 사용할 수 있다. Session 클래스를 따로 만들고 싶지 않다면 이 클래스를 사용하면 된다.
  
#### CSnowThread Class
- C++11 Thread가 아닌 _BeginThreadEx 함수를 사용하는 Thread로 Thread의 여러 기능들을 Class로 감싼 클래스이다. 아직 미미하지만 여러 기능을 넣을 예정이다.

#### Log Class
- Log를 출력할 수 있는 Log Class이다. 현재는 Print 기능만 지원하며 추후에 SaveLogFile을 지원할 예정이다.

#### CSnowServer Class
- Iocp기반 Server Class이다.

#### IocpCore class
- Iocp Handle을 가지는 Class이다. 이 클래스를 상속받는 Server가 CSnowServer Class이다.





