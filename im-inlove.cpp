// SFML 3.0.0
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <algorithm> // std::min, std::max

#include "what-if-i-frames.h" // WIDTH, HEIGHT, FRAME_SIZE, NUM_FRAMES, allFrames[][]

static void unpackFrameToImage(const uint8_t* frameBytes, sf::Image& out)
{
    // out đã có size WIDTH x HEIGHT
    for (unsigned y = 0; y < static_cast<unsigned>(HEIGHT); ++y)
    {
        for (unsigned x = 0; x < static_cast<unsigned>(WIDTH); ++x)
        {
            // 8 pixel ngang / 1 byte, MSB-first (bit 7 là pixel trái nhất)
            const unsigned byteIndex = y * (WIDTH / 8) + x / 8;
            const unsigned bitIndex  = 7 - (x % 8);
            const bool on = (frameBytes[byteIndex] >> bitIndex) & 0x1;

            // SFML 3: setPixel(sf::Vector2u, sf::Color)
            out.setPixel({x, y}, on ? sf::Color::White : sf::Color::Black);
        }
    }
}
int main() {
    const unsigned windowW = 480, windowH = 320;
    sf::RenderWindow window(sf::VideoMode({windowW, windowH}), "Frames Player (SFML 3)");
    window.setVerticalSyncEnabled(true);

    // Ảnh 128x64
    sf::Image img({static_cast<unsigned>(WIDTH), static_cast<unsigned>(HEIGHT)}, sf::Color::White);

    // Texture + Sprite (Sprite cần texture khi khởi tạo ở SFML 3)
    sf::Texture tex;
    bool ok = tex.loadFromImage(img);                // [[nodiscard]] -> phải dùng biến ok
    if (!ok) return 1;                               // xử lý lỗi tối thiểu
    sf::Sprite sp(tex);
    tex.setSmooth(false);

    // Scale & căn giữa
    const float scale = 4.f;
    sp.setScale({scale, scale});
    const float spriteW = WIDTH * scale, spriteH = HEIGHT * scale;
    sp.setPosition({(windowW - spriteW) / 2.f, (windowH - spriteH) / 2.f});

    std::size_t frameIdx = 0;
    bool paused = false;
    float fps = 14.f, frameTime = 1.f / fps;
    sf::Clock clock; float acc = 0.f;

    while (window.isOpen()) {
        // --- Điều khiển phát lại ---
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                using K = sf::Keyboard::Key;         // alias cho gọn

                if (key->code == K::Space) {
                    paused = !paused; 
                } else if (key->code == K::Up) {
                    fps = std::min(120.0f, fps + 1.0f);
                    frameTime = 1.0f / fps;
                } else if (key->code == K::Down) {
                    fps = std::max(1.0f, fps - 1.0f);
                    frameTime = 1.0f / fps;
                }

                if (paused && key->code == K::Right)
                    frameIdx = (frameIdx + 1) % NUM_FRAMES;
                if (paused && key->code == K::Left)
                    frameIdx = (frameIdx + NUM_FRAMES - 1) % NUM_FRAMES;
            }
        }

        // --- Cập nhật frame theo thời gian ---
        const float dt = clock.restart().asSeconds();
        acc += dt;
        if (!paused) {
            while (acc >= frameTime) {
                acc -= frameTime;
                frameIdx = (frameIdx + 1) % NUM_FRAMES;
            }
        }

        // --- Giải nén frame & nạp texture (phải dùng giá trị trả về) ---
        unpackFrameToImage(allFrames[frameIdx], img);
        ok = tex.loadFromImage(img);                 // [[nodiscard]]
        if (!ok) continue;                           // xử lí lỗi

        window.clear(sf::Color(30,30,30));
        window.draw(sp);
        window.display();
    }
    return 0;
  }


