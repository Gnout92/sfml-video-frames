# sfml-video-frames

## 📖 Giới thiệu 
`sfml-video-frames` là một dự án demo thể hiện cách:
- **Chuyển đổi video sang dữ liệu nhúng** (`frames.h`) bằng Python + OpenCV.
- **Hiển thị video nhúng** trong C++ sử dụng **SFML 3.0.0**.

Mục tiêu của repo là minh họa kỹ thuật nhúng video dạng 1-bit (đen/trắng) và phát lại bằng thư viện đồ họa, phục vụ showcase trong portfolio.

### ✨ Tính năng
- Script Python:
  - Cắt video thành các frame.
  - Chuyển thành ảnh 1-bit (đen/trắng).
  - Đóng gói thành file `frames.h`.
- Demo C++:
  - Đọc mảng `allFrames` từ `frames.h`.
  - Hiển thị bằng **SFML 3**.
  - Điều khiển tốc độ khung hình, tạm dừng, tua frame.

### 🚀 Cách chạy
 1. Chuẩn bị môi trường
- **Python 3.9+**
  ```bash
    pip install opencv-python numpy
   //C++17 và SFML 3.0.0 (MinGW / MSYS2).

 2. Tạo file frames.h từ video
     ```bash
     python frames_dir_to_header.py --frames-dir ./frames -o frames.h --width 128 --height 64 --threshold 127

 4. Biên dịch demo C++
      ```bash
    g++ player.cpp -o player -std=c++17 
    -I"path/to/SFML/include" 
    -L"path/to/SFML/lib" 
    -lsfml-graphics
    -lsfml-window
    -lsfml-system

6. Chạy
   ```bash
    ./player
🎮 Điều khiển trong chương trình

  Space: Tạm dừng / tiếp tục.
  
  ↑ / ↓: Tăng / giảm FPS.
  
  ← / →: Lùi / tiến 1 frame khi đang pause.

--------------------------------------------------------------------------------------------------------------------------------------------------
##📖 Introduction 

sfml-video-frames is a demo project showcasing how to:

Convert videos to embedded data (frames.h) using Python + OpenCV.

Play embedded video frames in C++ using SFML 3.0.0.

This project demonstrates embedding video as 1-bit frames and playing it back, suitable for portfolio showcases.

✨ Features

Python script:

Extract frames from video.

Convert to 1-bit (black/white).

Pack into frames.h.

C++ demo:

Reads allFrames array from frames.h.

Displays via SFML 3.

Supports playback speed control, pause, frame stepping.

🚀 How to run
1. Setup

- Python 3.9+
  ```bash
  pip install opencv-python numpy
  // C++17 compiler and SFML 3.0.0.

2. Generate frames.h from video
   ```bash  
    python frames_dir_to_header.py --frames-dir ./frames -o frames.h --width 128 --height 64 --threshold 127

3. Build demo
    ```bash
    g++ player.cpp -o player -std=c++17 \
      -I"path/to/SFML/include" \
      -L"path/to/SFML/lib" \
      -lsfml-graphics
      -lsfml-window
      -lsfml-system
4. Run
     ```bash
    ./player

🎮 Controls

  Space: Pause / Resume.
  
  ↑ / ↓: Increase / decrease FPS.
  
  ← / →: Step backward / forward when paused.



OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
