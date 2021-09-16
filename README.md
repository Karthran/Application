Консольный чат
Автор Мальцев Владислав

Описание Идеи

Пользовательские типы

template <typename T>
class Array     -    шаблонный динамический массив

class Utils     -    вспомогательные утилиты и макросы.

class User      -    данные пользователя( имя, логин, пароль и ID)

class Message   -    данные сообщения (автор, текст, время создания и редактирования)

class Chat      -    данные конкретного чата: 
             	     массив разделяемых указателей на объекты класса Message,
		     	   
               	     два указателя на пользователей чата(class User), если чат закрытый,
				     если общий - они равны nullptr. В закрытом чате в _first_user 
				     находится объект User с меньшим ID, в _second_user с большим ID.
			   
	         	     Содержит методы для работы с сообщениями(class Message):
			         печать, добавление, удаление и редактирование.
				 
				     При печати, номера сообщений начинаются с 1, но в массиве 
				     индексация начинается с 0, коррекция происходит после ввода
				     номера сообщения.

class Application -  Основной класс обеспечивающий работу приложения.
					 Производит вывод и обработку меню.
					
					 При создании нового пользователя добавляет его в массив разделяемых
					 указателей на объект User, ID пользователя совпадает с индексом.
                     При печати, ID пользователей начинаются с 1, но в массиве индексация
					 начинается с 0, коррекция происходит после ввода ID пользователя.
					
					 При	создании нового закрытого чата - указатель на объект Chat вставляется
					 в массив разделяемых указателей по индексу соответствующему значениям ID
					 переменных класса Chat _first_user и _second_user. Массив отсортирован по
					 возрастанию _first_user ID, блоки с одинаковым _first_user ID отсортированы
					 по возрастанию _second_user ID.

					 Указатель на общий чат всегда находится в массиве по индеку 0.

					 Обработку сообщений делегирует классу Chat 




