--
-- PostgreSQL database cluster dump
--

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION BYPASSRLS;






--
-- Database creation
--

CREATE DATABASE access_control WITH TEMPLATE = template0 OWNER = postgres;
REVOKE CONNECT,TEMPORARY ON DATABASE template1 FROM PUBLIC;
GRANT CONNECT ON DATABASE template1 TO PUBLIC;


\connect access_control

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: pgcrypto; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS pgcrypto WITH SCHEMA public;


--
-- Name: EXTENSION pgcrypto; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION pgcrypto IS 'cryptographic functions';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: admin; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.admin (
    id integer NOT NULL,
    username text NOT NULL,
    password text NOT NULL
);


ALTER TABLE public.admin OWNER TO postgres;

--
-- Name: admin_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.admin_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.admin_id_seq OWNER TO postgres;

--
-- Name: admin_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.admin_id_seq OWNED BY public.admin.id;


--
-- Name: log; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.log (
    id integer NOT NULL,
    user_id integer NOT NULL,
    enter_time timestamp(6) without time zone DEFAULT (now())::timestamp without time zone NOT NULL,
    exit_time timestamp(6) without time zone
);


ALTER TABLE public.log OWNER TO postgres;

--
-- Name: log_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.log_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.log_id_seq OWNER TO postgres;

--
-- Name: log_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.log_id_seq OWNED BY public.log.id;


--
-- Name: log_user_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.log_user_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.log_user_id_seq OWNER TO postgres;

--
-- Name: log_user_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.log_user_id_seq OWNED BY public.log.user_id;


--
-- Name: login_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.login_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.login_id_seq OWNER TO postgres;

--
-- Name: login; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.login (
    login_id integer DEFAULT nextval('public.login_id_seq'::regclass) NOT NULL,
    user_id integer NOT NULL,
    password text NOT NULL,
    active integer DEFAULT 1 NOT NULL
);


ALTER TABLE public.login OWNER TO postgres;

--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    user_id integer NOT NULL,
    name text NOT NULL,
    active integer DEFAULT 1 NOT NULL
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Name: matricula_matricula_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.matricula_matricula_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.matricula_matricula_id_seq OWNER TO postgres;

--
-- Name: matricula_matricula_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.matricula_matricula_id_seq OWNED BY public.users.user_id;


--
-- Name: admin id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.admin ALTER COLUMN id SET DEFAULT nextval('public.admin_id_seq'::regclass);


--
-- Name: log id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.log ALTER COLUMN id SET DEFAULT nextval('public.log_id_seq'::regclass);


--
-- Name: users user_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users ALTER COLUMN user_id SET DEFAULT nextval('public.matricula_matricula_id_seq'::regclass);


--
-- Data for Name: admin; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.admin VALUES (1, 'admin', '$2a$06$Lwow2.5ikyRDq60a1CRwzu/O.WmTF02V5w9v8JsTXtUI0gpcNiI.O');


--
-- Data for Name: log; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.log VALUES (1, 1, '2020-02-26 15:28:55.480012', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (2, 1, '2020-02-26 16:36:08.682858', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (3, 1, '2020-02-26 16:44:50.871045', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (4, 1, '2020-02-26 16:45:00.662545', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (5, 1, '2020-02-26 16:47:09.411945', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (6, 1, '2020-02-26 16:47:32.997904', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (7, 1, '2020-02-26 16:50:24.593853', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (8, 1, '2020-02-26 16:50:39.895051', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (9, 1, '2020-02-26 16:52:32.267962', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (10, 1, '2020-02-26 16:54:09.431253', '2020-02-26 16:54:16.104393');
INSERT INTO public.log VALUES (11, 1, '2020-02-26 16:59:08.722285', '2020-02-26 17:02:41.635992');
INSERT INTO public.log VALUES (12, 1, '2020-02-26 17:10:21.262544', '2020-02-26 17:10:28.025951');
INSERT INTO public.log VALUES (13, 3, '2020-02-26 17:50:44.837767', '2020-02-27 12:10:35.817673');
INSERT INTO public.log VALUES (14, 1, '2020-02-27 12:20:34.862413', '2020-02-27 12:20:43.16244');
INSERT INTO public.log VALUES (15, 1, '2020-02-27 13:44:58.521164', '2020-02-27 13:45:05.983381');
INSERT INTO public.log VALUES (16, 3, '2020-02-27 14:31:02.455323', '2020-02-27 14:31:15.877361');
INSERT INTO public.log VALUES (17, 1, '2020-02-28 10:28:28.416366', '2020-02-28 10:30:02.966224');
INSERT INTO public.log VALUES (18, 2, '2020-02-28 10:32:07.03134', '2020-02-28 10:33:30.139632');
INSERT INTO public.log VALUES (19, 4, '2020-02-29 18:51:56.945853', '2020-02-29 18:52:21.942432');
INSERT INTO public.log VALUES (20, 2, '2020-03-01 20:10:29.040864', '2020-03-01 20:10:35.565151');
INSERT INTO public.log VALUES (21, 4, '2020-03-02 00:24:39.67765', '2020-03-02 00:24:45.574683');
INSERT INTO public.log VALUES (22, 1, '2020-03-02 00:40:44.836724', '2020-03-02 00:40:51.063834');
INSERT INTO public.log VALUES (23, 5, '2020-03-02 00:55:06.925831', '2020-03-02 00:55:36.583077');


--
-- Data for Name: login; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.login VALUES (1, 1, '$2a$06$ZF3nJArUpytLtt2JftrRdeH03cPArcxgrIR1ZFC6vx6Vk/XIVLDWm', 1);
INSERT INTO public.login VALUES (3, 3, '$2a$06$8IjUwuwo5q.E4viq6q6MVOGBfK1.jg8zJnpjOh1.tnW9.XU5LW2tC', 1);
INSERT INTO public.login VALUES (4, 4, '$2a$06$uGoc8HBSOAO3a8lUj.JVRuggpRV1QyApwdeseZII1bAYTas02A27a', 1);
INSERT INTO public.login VALUES (2, 2, '$2a$06$TEuh1BcCda3dUaoqkA2dYuiELYBTMa6XTckXDEQzAQnLg6tzyzm/G', 1);
INSERT INTO public.login VALUES (5, 5, '$2a$06$UV89p7CIlkkw87oDVA/WOuZUWOUzgtQpvryCDMmNomx45eaUjp/02', 0);
INSERT INTO public.login VALUES (6, 5, '$2a$06$ZSeePfr/rmGSE9ifclSrzuLPoulk7F5gLz0nxUiUMcrzqo1bL6WfC', 1);


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.users VALUES (1, 'Josep Lliteres', 1);
INSERT INTO public.users VALUES (3, 'Catalina López', 1);
INSERT INTO public.users VALUES (4, 'Maria Antònia Oliver', 1);
INSERT INTO public.users VALUES (2, 'María López', 0);
INSERT INTO public.users VALUES (5, 'María Castaño', 0);


--
-- Name: admin_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.admin_id_seq', 2, true);


--
-- Name: log_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.log_id_seq', 23, true);


--
-- Name: log_user_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.log_user_id_seq', 1, false);


--
-- Name: login_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.login_id_seq', 6, true);


--
-- Name: matricula_matricula_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.matricula_matricula_id_seq', 5, true);


--
-- Name: admin admin_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.admin
    ADD CONSTRAINT admin_pkey PRIMARY KEY (id);


--
-- Name: log log_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.log
    ADD CONSTRAINT log_pkey PRIMARY KEY (id);


--
-- Name: login login_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.login
    ADD CONSTRAINT login_pkey PRIMARY KEY (login_id);


--
-- Name: users matricula_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT matricula_pkey PRIMARY KEY (user_id);


--
-- Name: login fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.login
    ADD CONSTRAINT fk1 FOREIGN KEY (user_id) REFERENCES public.users(user_id);


--
-- Name: log fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.log
    ADD CONSTRAINT fk1 FOREIGN KEY (user_id) REFERENCES public.users(user_id);


--
-- PostgreSQL database dump complete
--

\connect postgres

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: DATABASE postgres; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE postgres IS 'default administrative connection database';


--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- PostgreSQL database dump complete
--

\connect template1

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: DATABASE template1; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE template1 IS 'default template for new databases';


--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- PostgreSQL database dump complete
--

--
-- PostgreSQL database cluster dump complete
--

