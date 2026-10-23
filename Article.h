#pragma once

#include <string>

/**
 * @brief Класс Article (статья уголовного кодекса)
 */
class Article {
	private:
		/**
		 * @brief Номер статьи
		 */
		std::string number;

		/**
		 * @brief Характер преступления
		 */
		std::string title;

	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		Article() = default;

		/**
		 * @brief Конструктор
		 * @param number - номер статьи
		 * @param title - характер преступления
		 */
		Article(const std::string& number, const std::string& title);

		/**
		 * @brief Получить номер статьи
		 * @return номер статьи
		 */
		const std::string& getNumber() const noexcept;

		/**
		 * @brief Получить характер преступления
		 * @return характер преступления
		 */
		const std::string& getTitle() const noexcept;

		/**
		 * @brief Получить строку со статьёй
		 * @return строка вида "номер (характер преступления)"
		 */
		std::string toString() const;
};
