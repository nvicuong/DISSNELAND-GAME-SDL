# DISSNELAND GAME
Bài tập cuối học phần INT2215
- Tên sinh viên: Nguyễn Việt Cương
- Mã sinh viên: 22021211
- Trường Đại học Công nghệ - ĐHQG Hà Nội

## Mô tả chung về trò chơi

- game góc nhìn thứ 3 nhìn từ trên xuống, điều khiển nhân vật kiếm sĩ tiêu diệt hết quái để qua màn.

- Sử dụng phím a s d w để di chuyển, j để chém, k để né đòn.

- có 3 loại quái:
	+ Flying eye: di chuyển trong vùng cố định, có khả năng bắn đạn.
	+ Skeleton: dùng kiếm để chém, phạm vi hoạt động rộng, có khả năng săn lùng người chơi và tránh trường ngoại vật.
	+ Boss: dùng rìu để chém, có skill tốc biến truy lùng người chơi, phạm vi hoạt động toàn map, bất tử.

- Item rơi ra khi người chơi hạ gục một con quái, có 2 loại Item:
	+ thuốc kim cương: hồi phục 100% máu.
	+ thuốc vương liệm: x2 sát thương tấn công trong 10 giây (không cộng dồn).

- người chơi thua khi để nhân vật hết máu.

- Ở map thứ 2, khi máu xuống dưới 40%, nhấn E để giảng hòa => Win game.

## Các chức năng đã cài đặt
- Menu game
	- Menu chính xuất hiện khi bắt đầu mở game có các chức năng:
		+ Start: bắt đầu game
		+ Tutorial: hướng dẫn
		+ Sound ON/OFF: bật, tắt âm thanh
		+ Quit: thoát game
	- Menu pause, nhấn p để pause game:
		+ Continue: tiếp tục game
		+ Menu: quay trở lại Menu chính
		+ Quit: thoát game
	- Menu game over hiện lên sau khi người chơi thua:
		+ Menu: quay trở lại Menu chính
		+ Quit: thoát game
	- Menu game win hiện lên sau khi người chơi giảng hòa thành công:
		+ Menu: quay trở lại Menu chính
		+ Quit: thoát game
- Trong quá trình chơi có thể nhấn Esc hoặc bấm dấu X trên cửa sổ game để thoát game

## Các kiến thức đã sử dụng

- con trỏ

- mảng tĩnh, vector, bitset, map, thuật toán có sẵn trong thư viện algorithm

- Class

- sử dụng template

- thuật toán:
	+ xử lý va chạm
	+ xử lý camera đi theo nhân vật
	+ ứng dụng nội suy tuyến tính để nhân vật di chuyển và hiệu ứng khi bị dính đòn mượt mà hơn
	+ xử lý các chức năng bắn, chém, dính đòn cho hợp lý
	+ ứng dụng thuật toán tìm đường đi BFS để cho quái có thể vượt qua chuớng ngoại vật và nhanh nhất tìm đến nhân vật, nếu ngoài phạm vi hoạt động thì có thể trở lại vị trí cố định

- Sử dụng được một số thư viện SDL2:
	+ SDL
	+ SDL_image
	+ SDL_ttf
	+ SDL_mixer

## hướng dẫn cài đặt và trải nghiệm game

- mở main.exe để chơi hoặc vào cửa sổ TERMINAL, di chuyển đến folder game rồi gõ 'makefile'

## Hướng phát triển

- phát triển thêm cốt truyện, bổ sung map chơi, các loại quái mới, các chức năng mới.
- thêm chế độ endless, chế độ 2 người chơi.

## Nguồn tham khảo

- Em học và tham khảo những phần cơ bản trên kênh youtube: Let's Make Games.
- Âm thanh, hình ảnh xài chùa trên mạng.
- phần còn lại là tự phát triển.

## Những thứ học được qua quá trình thực hiện game

- có cái nhìn tổng quan về cấu trúc của một dự án.
- học thêm về Class, sử dụng các thư viện.
- ứng dụng của thuật toán trong việc hoàn thiện chức năng game.
- bắt đầu hình thành tư duy giải quyết vấn đề.


## Trân trọng ##