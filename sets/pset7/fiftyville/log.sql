-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To find desciption of the crime scene
SELECT description
FROM crime_scene_reports
WHERE year = 2020
AND month = 7
AND day = 28
AND street = "Chamberlin Street";


--Find names, witnesses and transcipt


-- Get name and transcript of all interviews conducted that day
SELECT name, transcript
FROM interviews
WHERE year = 2020
AND month = 7
AND day = 28
ORDER BY id;

--See all logs within one hour of the crime scene (LICENSE PLATES)
SELECT activity, license_plate, minute
FROM courthouse_security_logs
WHERE year = 2020
AND month = 7
AND day = 28
AND hour = 10
ORDER BY minute;

--NAMES OF LICENCE PLATES WITHING ONE HOUR 
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute < 26 
    AND minute > 14
    ORDER BY minute);



--Find atm transaction of THIEF
SELECT account_number, transaction_type, amount
FROM atm_transactions
WHERE atm_location = "Fifer Street"
AND year = 2020
AND month = 7
AND day = 28;

-- Names of people who withdrew money that day
SELECT name
FROM people
WHERE id IN(
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN(
        SELECT account_number
        FROM atm_transactions
        WHERE atm_location = "Fifer Street"
        AND year = 2020
        AND month = 7
        AND day = 28));

--Find numbers  of people who called each other for less than a minute
SELECT caller, receiver
FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 61;

--FIND NAMES of people who called for less than a minute  (TO FIND ACCOMPLICE. Who the thief talked to..)
SELECT name
FROM people
WHERE phone_number IN(
    SELECT receiver
    FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 61);
    


--Find early morning flights (earliest)
SELECT id, hour, minute
FROM flights
WHERE year = 2020
AND month = 7
AND day = 29
AND origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = "Fiftyville");

--Find id location of destination
SELECT destination_airport_id
FROM flights
WHERE year = 2020
AND month = 7
AND day = 29
AND origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = "Fiftyville")
AND id = 36;

-- Find name of location
SELECT city, full_name
FROM airports
WHERE id = 4;

-- Check passengers on that flight
SELECT name, phone_number
FROM people
WHERE passport_number IN(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36);

-- Check passengers that have licences that compare with the theft
SELECT name, phone_number
FROM people
WHERE passport_number IN(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36)
AND license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    );
    
--Match between licences, flight, and caller (suspect) 
SELECT name
FROM people
WHERE passport_number IN(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36)
AND license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10)
AND phone_number IN(
    SELECT receiver
    FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 61);

  --Match between licences, flight, and receiver (accomplice) 
SELECT name
FROM people
WHERE passport_number IN(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36)
AND license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10)
AND phone_number IN(
    SELECT receiver
    FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 61)
AND name IN(
    SELECT name
    FROM people
    WHERE id IN(
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE atm_location = "Fifer Street"
            AND year = 2020
            AND month = 7
            AND day = 28)));


-- Seat of accomplice (7B)
SELECT seat 
FROM passengers
WHERE flight_id = 36
AND passport_number IN (
    SELECT passport_number
    FROM people
    WHERE passport_number IN(
        SELECT passport_number
        FROM passengers
        WHERE flight_id = 36)
    AND license_plate IN (
        SELECT license_plate
        FROM courthouse_security_logs
        WHERE year = 2020
        AND month = 7
        AND day = 28
        AND hour = 10)
    AND phone_number IN(
        SELECT receiver
        FROM phone_calls
        WHERE year = 2020
        AND month = 7
        AND day = 28
        AND duration < 61));

--WHO sits next to accomplice 
SELECT name
FROM people
WHERE passport_number IN(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
    AND seat = "7A");





