-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
    FROM crime_scene_reports
    WHERE month = 7
    AND day = 28
    AND street = "Humphrey Street"; -- Checking a description of the crime in question

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT *
    FROM interviews
    WHERE month = 7
    AND day = 28; -- reading the interviews

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT *
    FROM atm_transactions
    WHERE month = 7
    AND day = 28
    AND transaction_type = "withdraw"
    AND atm_location = "Leggett Street";
    -- following interview #2 advice

SELECT *
    FROM people JOIN bank_accounts ON person_id = people.id
    WHERE account_number IN
       (SELECT account_number FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street");
        -- getting all info about everyone that withdrew at the crime day at Legett

/*+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
| 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       | 86363979       | 948985    | 2010          |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       | 16153065       | 458378    | 2012          |
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 28296815       | 395717    | 2014          |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 396669    | 2014          |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 467400    | 2014          |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 449774    | 2015          |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 81061156       | 438727    | 2018          |
+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+*/

SELECT *
    FROM people JOIN bank_accounts ON person_id = people.id
    WHERE account_number IN
       (SELECT account_number FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street")
    AND license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND activity = "exit");
        -- getting all the personal info about people that withdrew at legett and left the bakery parking lot

/*+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
| 396669 | Iman   | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 396669    | 2014          |
| 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 467400    | 2014          |
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 449774    | 2015          |
+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+*/

SELECT *
    FROM phone_calls
    WHERE caller IN
    (SELECT phone_number
        FROM people JOIN bank_accounts ON person_id = people.id
        WHERE account_number IN
        (SELECT account_number FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = "Leggett Street")
        AND license_plate IN
            (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND activity = "exit"))
    AND year = 2021
    AND month = 7
    AND day = 28;
    -- checking who from the people above made any calls that day


/*+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 236 | (367) 555-5533 | (344) 555-9601 | 2021 | 7     | 28  | 120      |
| 245 | (367) 555-5533 | (022) 555-4052 | 2021 | 7     | 28  | 241      |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 284 | (286) 555-6063 | (310) 555-8568 | 2021 | 7     | 28  | 235      |
| 285 | (367) 555-5533 | (704) 555-5790 | 2021 | 7     | 28  | 75       |
+-----+----------------+----------------+------+-------+-----+----------+*/
-- Iman and Luca didn't make any calls, so we can rule them out (manually checked that with ctlr + f)

-- suspect list after that:
/*+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 449774    | 2015          |
+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+*/

-- manually checking each flight on 29th of july 2021
 SELECT *
    FROM flights JOIN passengers ON flights.id = flight_id
    WHERE passport_number = 5773159633
    AND year = 2021
    AND month = 7
    AND day = 29;

SELECT *
    FROM flights JOIN passengers ON flights.id = flight_id
    WHERE passport_number = 3592750733
    AND year = 2021
    AND month = 7
    AND day = 29;

SELECT *
    FROM flights JOIN passengers ON flights.id = flight_id
    WHERE passport_number = 1988161715
    AND year = 2021
    AND month = 7
    AND day = 29;

/*+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+*/

/*+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 3592750733      | 4C   |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+*/

/*+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1988161715      | 6D   |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+*/

-- based on what interviewer #3 said, we can rule out Diana, because 16 hours is not an earliest flight

-- suspect list after that:
/*+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 449774    | 2015          |
+--------+--------+----------------+-----------------+---------------+----------------+-----------+---------------+*/

SELECT *
    FROM airports
    WHERE id = 4;
    -- since destination airport is the same for Tyler and Bruce, we can find out the final destination of a thief: New York City

-- checking when did the suspects leave the parking lot
SELECT *
    FROM bakery_security_logs
    WHERE license_plate = "94KL13X"
    AND activity = "exit";

SELECT *
    FROM bakery_security_logs
    WHERE license_plate = "1106N58"
    AND activity = "exit";

/*+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
+-----+------+-------+-----+------+--------+----------+---------------+

+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
+-----+------+-------+-----+------+--------+----------+---------------+*/

-- based on what interviewer #1 said we can say that Bruce is the thief

-- interviewer #3 said about a phone call that lasted less than a minute, Thus, the accomplice is Robin
SELECT *
    FROM people
    WHERE phone_number = "(375) 555-8161";

/*+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+*/