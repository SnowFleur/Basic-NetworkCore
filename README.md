# Basic-SnowNetCore SINCE 2021

### 환경 및 사용한 툴, 언어
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)
![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)
- C++17, X64

### 목적
- 네트워크 테스트를 위해 Code를 반복 제작하는 것을 방지하기 위해 만든 공개용 Network Core Library
- Send 와 Recv가 가능할 정도의 정말 단순한 기능만 지원을 한다.


### ❗️ 유의 사항
- IOCP는 추후에 넣을 가능성이 있음 현재는 기본적인 블럭킹/논블럭킹 Socket만 지원
- 버퍼 관리, 스레드 관리 기능등은 넣지 않았음
- TCP/IP 프로토콜에서 발생할 수 있는 문제 또한 모든 부분을 상정하지는 않음
- 버그가 있을 수 있음
- 급하게 작성했기 때문에 추후 구조의 변화 및 Source Code 변화가 있을 수 있음
- 그럴일 없겠지만 누구나 수정 및 재배포 가능(사용한다고만 알려주시면 됩니다.)


### 🔨 업데이트 예정 ✅: 업데이트 완료
- Singleton 기반 Log Class✅
- C++17기능 (std::stirng_view, std::any)
- Smart Pointer 도입 고려
- 구글의 Protocol Buffer를 사용해서 테스트 프로젝트를 올릴 예정(프로젝트 테스트도 해야함)
  
 

### ✅ 주요 클래스 설명 및 기능

#### CSnowSocket Class
- 기존 WinSocket을 Class 형태로 감싼 클래스로 Socket의 여러 기능을 사용할 수 있다.

#### CSnowSession Class
- 실제로 네트워크 통신을 진행할 Session Class로 CSnowSocket을 상속받고 있으며 Send, Recv, Bind 등의 기능을 사용할 수 있다. Session 클래스를 따로 만들고 싶지 않다면 이 클래스를 사용하면 된다.
  
#### CSnowThread Class
- C++11 Thread가 아닌 _BeginThreadEx 함수를 사용하는 Thread로 Thread의 여러 기능들을 Class로 감싼 클래스이다. 아직 미미하지만 여러 기능을 넣을 예정이다.

  





