DO$$
DECLARE

    v_num INT := 34;

    v_a INT :=0;
    v_b INT :=1;
    v_temp INT ;
    v_isFibonacci BOOLEAN := FALSE;

BEGIN 

    IF v_num < 50 THEN
        RAISE NOTICE 'The number % is LESS than 50.', v_num;
    ELSE
        RAISE_NOTICE 'The number % is NOT less than 50', v_num;

    END IF;


IF v_num = 0 OR v_num = 1 THEN
    v_isFibonacci := TRUE;

ELSE

    WHILE v_b < v_num LOOP
        v_temp := v_b;
        v_b := v_a + v_b;
        v_a := v_temp;
    END LOOP;


    IF v_b = v_num THEN 
        v_isFibonacci := TRUE ;

    END IF;
END IF;

    IF v_isFibonacci THEN
        RAISE NOTICE 'The number % is a Fibonacci number.', v_num;
    ELSE
        RAISE NOTICE 'The number % is NOT a Fibonacci number.', v_num;
    END IF;
END $$;