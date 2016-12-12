ceo = create_employee(first_name="Big" last_name="Boss")
new_company(director=ceo name="LAB3 LTD")
set_salary(employee=ceo salary=4000)

sales_head = create_employee(first_name="Barney" last_name="Stinson")
employ(employee=sales_head supervisor=ceo position="Sales Head" salary=2000)

tech_lead = create_employee(first_name="Marshall" last_name="Erickson")
employ(employee=tech_lead supervisor=ceo position="Tech Lead" salary=3000)

sales1 = create_employee(first_name="Robin" last_name="Scherbatsky")
employ(employee=sales1 supervisor=sales_head position="Sales manager" salary=1500)

sales2 = create_employee(first_name="Neil Patrick" last_name="Harris")
employ(employee=sales2 supervisor=sales_head position="Sales manager" salary=1600)


dev1 = create_employee(first_name="Ted" last_name="Mosby")
employ(employee=dev1 supervisor=tech_lead position="Software developer" salary=2100)

dev2 = create_employee(first_name="Lily" last_name="Aldrin")
employ(employee=dev2 supervisor=tech_lead position="Software developer" salary=1900)


save_to_file(company=company(employee=ceo) file="example.json")
