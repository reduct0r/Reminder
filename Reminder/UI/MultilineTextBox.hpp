#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace ReminderUI
{
    class MultiLineTextBox {

    private:
        bool _isFocused{ false };
        sf::Vector2f _position, _size;
        sf::RectangleShape _background;
        sf::Text _text;
        std::string _content;
        size_t _cursorPosition;

        sf::RectangleShape _cursor;
        bool _showCursor{ true };
        float _cursorBlinkTime{ 0.0f };

        bool _mouseLeftDown{ false };

        const sf::Font& _font;
        unsigned int _fontSize;

        bool _isBackspaceHeld = false;
        sf::Clock _backspaceClock;
        sf::Time _backspaceInterval = sf::milliseconds(1000);

        void updateCursor() {
            sf::Text locator(_text);
            locator.setString(_content);

            if (_cursorPosition > _content.size()) {
                _cursorPosition = _content.size();
            }

            sf::Vector2f cursorPos = locator.findCharacterPos(_cursorPosition);
            _cursor.setPosition(cursorPos);
        }

        void moveCursorVertical(int direction) {
            size_t lineNumber = 0, lineIndex = 0;
            for (size_t i = 0; i < _content.size(); ++i) {
                if (_content[i] == '\n') {
                    lineNumber++;
                    if (i >= _cursorPosition) {
                        lineIndex = i;
                        break;
                    }
                }
            }

            if (lineNumber == 0 && direction < 0) return; // Can't move up if already on first line.

            size_t newCursorPos = _cursorPosition + direction * (_cursorPosition - lineIndex);

            if (newCursorPos >= 0 && newCursorPos < _content.size())
                _cursorPosition = newCursorPos;

            updateCursor();
        }

        std::string getWrappedContent() const {
            std::string wrappedContent;
            sf::Text locator(_text);
            locator.setString("");

            for (char c : _content) {
                locator.setString(locator.getString() + c);

                if (locator.getGlobalBounds().width > _size.x - 8) {
                    size_t pos = wrappedContent.find_last_of(' ');

                    if (pos != std::string::npos) {
                        size_t spacePos = wrappedContent.find_last_not_of(' ');

                        if (spacePos != std::string::npos && spacePos == pos) {
                            wrappedContent.insert(pos, "\n");
                        }
                        else {
                            wrappedContent.replace(pos, 1, "\n");
                        }

                        locator.setString(wrappedContent.substr(pos + 1));
                    }
                    else {
                        wrappedContent += '\n';
                        locator.setString(c);
                    }
                }
                else {
                    wrappedContent += c;
                }

                // Проверка высоты текста
                if (locator.getGlobalBounds().height > _size.y - 8) break;
            }

            return wrappedContent;
        }

        void wrapText() {
            _content = getWrappedContent();
            _text.setString(_content);
        }


    public:
        MultiLineTextBox(float x, float y, float width, float height, const sf::Font& font, unsigned int fontSize)
            : _position(x, y),
            _size(width, height),
            _font(font),
            _fontSize(fontSize),
            _cursorPosition(0),
            _mouseLeftDown(false) 
        {
            _background.setSize(_size);
            _background.setPosition(_position);
            _background.setFillColor(sf::Color::White);

            _text.setFont(_font);
            _text.setCharacterSize(_fontSize);
            _text.setPosition(x, y);
            _text.setFillColor(sf::Color::Black);

            _cursor.setSize(sf::Vector2f(2, static_cast<float>(_fontSize)));
            _cursor.setFillColor(sf::Color::Black);
            updateCursor();
        }

        void setPos(float x, float y)
        {
            this->_position = sf::Vector2f(x, y);
            _background.setPosition(_position);
            _text.setPosition(x, y);
        }

        void setSize(float x, float y)
        {
            this->_size = sf::Vector2f(x, y);
            _background.setSize(_size);
            _background.setPosition(_position);

        }

        std::string getInput() const {
            return _text.getString();
        }

        void clearInput()
        {
            this->_text.setString("");
            this->_content = "";
        }

        void handleEvent(const sf::Event& event) {
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                    if (_background.getGlobalBounds().contains(mousePos)) {
                        _isFocused = true;
                        _showCursor = 1;
                        setCursorPositionFromMouse(mousePos);
                    }
                    else {
                        _isFocused = false;
                        _showCursor = false;  // Скрываем курсор
                    }
                }
                break;

            case sf::Event::TextEntered:
                if (!_isFocused) {
                    return;
                }

                if (event.text.unicode == 8) { // Backspace
                    if (!_content.empty() && _cursorPosition > 0) {
                        _content.erase(--_cursorPosition, 1);
                        wrapText();
                        updateCursor();
                    }
                }
                else if (event.text.unicode == 13) { // Enter
                    _content.insert(_cursorPosition++, "\n");
                    //wrapText();
                    updateCursor();
                }
                else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                    _content.insert(_cursorPosition++, 1, static_cast<char>(event.text.unicode));
                    wrapText();
                    updateCursor();
                }
                break;

            case sf::Event::KeyPressed:
                if (!_isFocused) {
                    return;
                }
                if (event.key.code == sf::Keyboard::Backspace and _isBackspaceHeld) {
                    _isBackspaceHeld = true;
                    _backspaceClock.restart();
                    if (!_content.empty() && _cursorPosition > 0) {
                        _content.erase(--_cursorPosition, 1);
                        wrapText();
                        updateCursor();
                    }
                }
                else if (event.key.control && event.key.code == sf::Keyboard::C) {
                    copyTextToClipboard();
                }
                else if (event.key.control && event.key.code == sf::Keyboard::V) {
                    pasteTextFromClipboard();
                }

                else {
                    switch (event.key.code) {
                    case sf::Keyboard::Left:
                        if (_cursorPosition > 0) {
                            _cursorPosition--;
                        }
                        updateCursor();
                        break;
                    case sf::Keyboard::Right:
                        if (_cursorPosition < _content.size()) {
                            _cursorPosition++;
                        }
                        updateCursor();
                        break;
                    default:break;
                    }
                }
                break;

            case sf::Event::KeyReleased:
                if (!_isFocused) {
                    return;
                }

                if (event.key.code == sf::Keyboard::Backspace) {
                    _isBackspaceHeld = false;
                }
                break;
            }
        }

        void setCursorPositionFromMouse(const sf::Vector2f& mousePos) {
            sf::Text locator(_text);
            locator.setString(_text.getString());
            for (size_t i = 0; i < _text.getString().getSize(); ++i) {
                sf::Vector2f charPos = locator.findCharacterPos(i);
                if (mousePos.x < charPos.x + _text.getCharacterSize() / 2.f &&
                    mousePos.y < charPos.y + _text.getCharacterSize()) {
                    _cursorPosition = i;
                    updateCursor();
                    return;
                }
            }
            _cursorPosition = _text.getString().getSize();
            updateCursor();
        }

        void copyTextToClipboard() {
            sf::Clipboard::setString(_content);
        }

        void pasteTextFromClipboard() {
            std::string clipboardContent = sf::Clipboard::getString();
            _content.insert(_cursorPosition, clipboardContent);
            _cursorPosition += clipboardContent.size();
            wrapText();
            updateCursor();
        }

        void update(float deltaTime) {
            if (_isFocused) 
            {
                if (_cursorBlinkTime >= 0.5f) {
                    _showCursor = !_showCursor;
                    _cursorBlinkTime = 0.1;
                }
                _cursorBlinkTime += deltaTime;
            }
            else 
            {
                _showCursor = false;  // Скрываем курсор, если текстбокс не в фокусе
                _cursorBlinkTime = 0.0f;  // Сбрасываем время мигания
            }
        }

        void draw(sf::RenderTarget* target) const {
            target->draw(_background);
            target->draw(_text);
            if (_showCursor) target->draw(_cursor);
        }

    };

}