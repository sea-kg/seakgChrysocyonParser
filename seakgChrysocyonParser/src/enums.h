#ifndef __SEAKG_CHRYSOCYON_ENUMS_H__
#define __SEAKG_CHRYSOCYON_ENUMS_H__

namespace seakgChrysocyon
{

	//-----------------------------------------------
	// ENUM : ANSWER TYPE

	enum chrysocyonAnswer
	{
		schsNone = 0, // точно нет или я отказываюсь
		schsYetUnknown = 1, //еще не знаю или еще не определился давай дальше
		schsMaybe = 2, // Может быть мое
		schsOnlyMe = 3, // Точно мое ( и должно быть только мое )
		schsComplete = 4, // да я закончил можешь забирать результат
	};

	//-----------------------------------------------
	// ENUM : ERROR OF TYPE

	enum chrysocyonErrors
	{
		chsErrEof = -1, // неожиданные конец файла
		chsErrUnknownAnswer = -2, // неизвестный ответ
		chsErrNotFoundPuppy = -3, // ненайден щенок
		chsErrTooManyPuppiesSayOnlyMe = -4, // более одного щенка заявили на права
		chsErrTooManyPuppiesSayCompleted = -5, // более одного щенка заявили что закончили
		chsErrUnknown = -6, // более одного щенка заявили что закончили
		chsErrNotFoundPuppyComplete = -7 // Ошибка в базовом механизме
	};
};

#endif // __SEAKG_CHRYSOCYON_ENUMS_H__
