text = "Демонстрация поиска по структуре компании и вывода в различных форматах\n"
print(var="text")

company = load_from_file(file="example.json")
text = strcat(s1="Название компании: " s2=company_name(company=company))
print(var="text")

text = "Структура по прямому подчинению:"
print(var="text")
text = print_hierarchy(company=company mode="subord")
print(var="text")

text = "Структура по высоте позиции:"
print(var="text")
text = print_hierarchy(company=company mode="level")
print(var="text")

text = "Поиск сотрудников с окладом выше 2000:"
print(var="text")
result = filter_by_salary(company=company salary=2000)
print(var="result")

text = "\nПоиск непосредственных подчиненных директора:"
print(var="text")
result = subordinates(employee=director(company=company))
print(var="result")

text = "\nПоиск сотрудников на позиции Software developer:"
print(var="text")
result = filter_by_position(company=company position="Software developer")
print(var="result")

