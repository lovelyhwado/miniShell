#This is my README

간단한 쉘 프로그램입니다.


// 헤더

1. headers.h 사용한 헤더들이 include 되어 있습니다
2. input.h input.c에서 사용한 매크로와 함수가 정의되어 있습니다
3. functions.h 일반적인 기능들을 사용할 때 필요한 함수가 정의되어 있습니다.

//c 파일

1. minishell.c 메인 루프가 돌아갑니다
2. input.c 입력을 받고 쉘 프롬프트를 띄웁니다
3. functions.c 입력을 파싱해서 실행시킵니다
4. history.c 히스토리 파일을 만들고 history, !숫자, !! 명령어를 사용 할 수 있게 합니다
5. redirection_pipe.c 파이프와 리다이렉션을 구현합니다

파이프는 ls | cat 은 되는데 ls | more 이건 안됩니다
리다이렉션은 여러개 있으면 안됩니다

