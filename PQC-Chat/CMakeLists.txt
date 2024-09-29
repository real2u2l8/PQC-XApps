cmake_minimum_required(VERSION 3.10)
project(PQC-Chat)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 여러 서브디렉토리 추가
foreach(dir IN ITEMS 
    App/wxChat # 메인 실행
    App/tcpclient-test
    App/tcpserver-test
    App/tlsclient-test
    App/tlsserver-test
    App/vpnclient-test
    App/vpnserver-test
)
    add_subdirectory(${dir})
endforeach()
