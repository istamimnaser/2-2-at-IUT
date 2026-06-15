CREATE OR REPLACE FUNCTION  process_salary_update()
RETURNS TRIGGER AS $$
DECLARE
    v_increase_percentage NUMERIC(5,2);
BEGIN

    IF NEW.salary = OLD.salary THEN
        RETURN NEW; 
    END IF;

    IF NEW.salary < OLD.salary THEN
    RAISE EXCEPTION 'Salary cannot be decreased. Old Salary: %, Attempted New Salary: %', OLD.salary, NEW.salary;
    END IF;


    IF OLD.salary > 0 THEN
        v_increase_percentage := ((NEW.salary - OLD.salary) / OLD.salary) * 100;
    ELSE
        v_increase_percentage := 0; 
    END IF;

    IF v_increase_percentage > 20 THEN
        RAISE EXCEPTION 'Salary increase of % exceeds the 20% limit. Old Salary: %, Attempted New Salary: %', v_increase_percentage, OLD.salary, NEW.salary;
    END IF;


    INSERT INTO Salary_Audit(emp_id, emp_name,  old_salary, new_salary, increase_percent, update_time)
    values (NEW.emp_id, NEW.emp_name, OLD.salary, NEW.salary, v_increase_percentage, NOW());

    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER trg_salary_update
BEFORE UPDATE OF salary ON Employee
FOR EACH ROW
EXECUTE FUNCTION process_salary_update();