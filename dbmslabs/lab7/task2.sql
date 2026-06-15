DO$$
DECLARE 
    v_distanceCenter INT ;
    v_stars INT ;
    v_row TEXT;
BEGIN 

    FOR i IN 1..9 LOOP

        v_distanceCenter := abs(5-i);

        v_stars := 9 - (2* v_distanceCenter);

       FOR j IN 1..v_distance_from_center LOOP
            v_row_string := v_row_string || '-';
        END LOOP;
        
       
        FOR k IN 1..v_stars LOOP
            v_row_string := v_row_string || '*';
        END LOOP;
        
        
        FOR l IN 1..v_distance_from_center LOOP
            v_row_string := v_row_string || '-';
        END LOOP;


        RAISE NOTICE '%', v_row;

    END LOOP;
END $$;