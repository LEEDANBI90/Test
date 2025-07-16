# Race Condition Practice Files

## 설명
이 저장소는 정보보안 교육용 레이스 컨디션 실습 파일들을 포함합니다.

## 파일 구성
- `race_vulnerable.c`: 취약한 프로그램 (TOCTTOU 취약점)
- `race_attack.sh`: 공격 스크립트
- `race_safe.c`: 안전한 프로그램 (방어 기법 적용)

## 사용법
```bash
# 컴파일
gcc -o vulnerable race_vulnerable.c
gcc -o safe race_safe.c

# 실행 권한 부여
chmod +x race_attack.sh

# 실행
./race_attack.sh  # 터미널 1
./vulnerable      # 터미널 2
