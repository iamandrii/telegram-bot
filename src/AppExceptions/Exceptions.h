#pragma once

#include <bits/stdc++.h>
using namespace std;
namespace App{
	class Exception : public exception {
	protected:
		char* msg;
		const char* className = "Exception";
	public:
		Exception();
		Exception(char* msg);

		const char* what() const throw();
	};

	namespace Exceptions{
		class PostgresError : public App::Exception{
		private:
			int errorStatus;
			const char* errorMessage;
			const char* className = "PostgresError";
		public:
			PostgresError();
			PostgresError(const char* dberr, int dbstat);
		};

		class IdentifierError : public App::Exception{
		private:
			const char* modifier;
			const char* className = "IdentifierError";
		public:
			IdentifierError();
			IdentifierError(const char* modifier, const char* msg);
		};

		class UndefinedVariableError : public App::Exception{
		private:
			const char* className = "UndefinedVariableError";
		public:
            UndefinedVariableError(const char* message);
		};

        class DatabaseUnsetError : public App::Exceptions::UndefinedVariableError{
        private:
            const char* className = "DatabaseUnsetError";
        public:
            DatabaseUnsetError();
        };

		class NotImplementedError : public App::Exception{
		private:
			const char* className = "NotImplementedError";
		public:
			NotImplementedError();
		};
	}
}