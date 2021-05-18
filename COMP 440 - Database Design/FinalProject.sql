-- JORDAN BRADSHAW
-- 440
-- MW 5:30
-- Prof Mushkatblat
USE [cs440mw25]
/*
-----------SQLECTRON DOESNT ALLOW GO STATEMENTS SO HAVE TO DO PROCEDURES INDIVIDUALLY :(--------
------------------------------DROP PROCEDURES-------------------------
DROP PROCEDURE getProductID
DROP PROCEDURE rptCounts
DROP PROCEDURE updVersionToDec
-----------------------------PROCEDURES------------------------------
----MIGHT HAVE TO RUN ONE BY ONE SINCE THERES NO GO AND SQLECTRON WAS HAVING AN ISSUE

--------------------------------- GET PRODUCT ID PROCEDURE-------------------------------------------
CREATE PROCEDURE getProductID
AS
BEGIN
    RETURN (SELECT product_id FROM products WHERE product_name = 'DEFAULT')
END

-----------------------------------GET rptCounts PROCEDURE-----------------------------------------------
CREATE PROCEDURE rptCounts
AS
BEGIN
-----DECLARE VAR
    DECLARE @featuresCount int;
    DECLARE @storiesCount int;
    DECLARE @tasksCount int;
    DECLARE @bugsCount bigint;
---- GET COUNTS
    SET @featuresCount = (SELECT COUNT(type_name) FROM hierarchies WHERE type_name = 'Feature')
    SET @storiesCount = (SELECT COUNT(type_name) FROM hierarchies WHERE type_name = 'User Story')
    SET @tasksCount = (SELECT COUNT(type_name) FROM hierarchies WHERE type_name = 'Task')
    SET @bugsCount = (SELECT COUNT(type_name) FROM hierarchies WHERE type_name = 'Bug')
    ---CREATE TEMP TABLE
    CREATE TABLE [dbo].[response](
    [Count] [varchar](max) NOT NULL,
    );
    INSERT response
    VALUES ('Features'),
    (cast(@featuresCount as varchar)),
    ('User Stories'),
    (cast(@storiesCount as varchar)),
    ('Tasks'),
    (cast(@tasksCount as varchar)),
    ('Bugs'),
    ('So by XYZ you meant you wanted them added -> ' + cast((@featuresCount + @storiesCount + @tasksCount) as varchar) + ' <- Or if you wanted actual bugs count -> ' + cast(@bugsCount as varchar));
    SELECT * FROM response
    IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[response]') AND type in (N'U'))
    DROP TABLE [dbo].[response]
END

---------------------------------GET updVersionToDec PROCEDURE------------------------------------------------
CREATE PROCEDURE updVersionToDec
    @versionChar VARCHAR(30)
AS
BEGIN
    DECLARE @versionID BIGINT;
    SET @versionID = (SELECT version_id FROM versions WHERE version_name = @versionChar)
    UPDATE versions
    SET version_name = CONCAT(@versionChar,'0') WHERE version_id = @versionID
END
----------------------------------------END OF PROCEDURES--------------------------------------------------
*/
---- JUST IN CASE CRASHED
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[response]') AND type in (N'U'))
    DROP TABLE [dbo].[response]
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[hierarchies]') AND type in (N'U'))
DROP TABLE [dbo].[hierarchies]
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[versions]') AND type in (N'U'))
DROP TABLE [dbo].[versions]
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[releases]') AND type in (N'U'))
DROP TABLE [dbo].[releases]
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[products]') AND type in (N'U'))
DROP TABLE [dbo].[products]
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[spreadSheet]') AND type in (N'U'))
DROP TABLE [dbo].[spreadSheet]

--PRODUCTS -> RELEASES -> SUBVERSIONS
----------------------------------------------------------------------------
 CREATE TABLE [dbo].[products](  
        [product_id] [tinyint] IDENTITY(1,1) NOT NULL,
        [product_name] [varchar](max) NOT NULL,
        [create_date] [date] NULL,
        CONSTRAINT [product_pk] PRIMARY KEY (product_id),
        );
        
 CREATE TABLE [dbo].[releases](
        [release_id] [int] IDENTITY(1,1) NOT NULL,
        [product_id] [tinyint] NOT NULL FOREIGN KEY REFERENCES products(product_id),
        [release_version] [varchar](10) NOT NULL,
        CONSTRAINT [release_pk] PRIMARY KEY (release_id),
        CONSTRAINT [release_uc] UNIQUE (product_id,release_version),
        );

CREATE TABLE [dbo].[versions](
        [version_id] [bigint] IDENTITY(1,1) NOT NULL,
        [release_id] [int] NOT NULL FOREIGN KEY REFERENCES releases(release_id),
        [version_name] [varchar](10) NOT NULL,
        [notified_date] [date] NULL,
        [release_date] [date] NULL,
        CONSTRAINT [version_pk] PRIMARY KEY (version_id),
        CONSTRAINT [version_uc] UNIQUE (release_id,version_name),
        );
        
CREATE TABLE [dbo].[hierarchies] (
        [hierarchy_pid] [bigint]  NOT NULL,
        [type_name] [varchar](14) NOT NULL,
        [hierarchy_ppid] [bigint] NULL,
        [object_title] [varchar](max) NOT NULL,
        [object_description] [varchar](max) NULL,
        [activity] [varchar](12) NOT NULL,
        [soa_name] [varchar](14) NOT NULL,
        [reported_name] [varchar](14) NOT NULL,
        [created_date] [date] NOT NULL,
        [recorded_date] [date] NULL,
        [version_id] [bigint] NOT NULL FOREIGN KEY REFERENCES versions(version_id),
        CONSTRAINT [hierarchy_pk] PRIMARY KEY (hierarchy_pid), 
        );
-------------------------------------------------------------------------
---SCRIPT PRELOAD DEFAULT PRODUCT
INSERT INTO products(product_name,create_date)
VALUES ('DEFAULT','1/1/2000')

CREATE TABLE [dbo].spreadSheet (
    row_id [bigint] IDENTITY(1,1) NOT NULL, 
    pid BIGINT,
    type_char VARCHAR(11),
    ppid BIGINT,
    title [varchar](max),
    description [varchar](max),
    activity [varchar](12),
    created_date date,
    soa [varchar](14),
    reported_by [varchar](14),
    recorded_date date,
    release_version [varchar](10),
    release_date date,
    notification_date date,
    software_version [varchar](10),
    );
    
INSERT INTO spreadSheet
VALUES 
/* INSERT QUERY NO: 1 */
(1, 'Feature', '', 'WebSite Content', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Development', '12/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.1'),
/* INSERT QUERY NO: 2 */
(4, 'User Story', '1', 'Current layout needs change to the new look', 'orem ipsum dolor sit amet, consectetur adipiscing elit. Etiam condimentum odio sed mi vehicula consequat. ngue, sit amet mattis ex porta.', 'Development', '1/1/2018', 'TFS', 'HH', '12/25/2017', '1.1.8', '2/2/2018', '1/30/2018', '1.1.8.1'),
/* INSERT QUERY NO: 3 */
(5, 'Task', '4', 'Change the website CSS file to implement colors, fonts, logo, and layout', 'orem ipsum dolor sit amet, consectetur adipiscing elit. Etiam condimentum odio sed mi vehicula consequat. Nulla condimentum neque id convallis bibendum.  vehicula auctor. Morbi mattis, tortor in rutrum faucibus, felis quam interdum ipsum, eu molestie ante dolor et leo. Nullam fringilla vel nisi non tincidunt. Praesent commodo, nunc ac venenatis consectetur, nunc massa tristique risus, ut ultrices tellus nunc at augue. Suspendisse potenti. Suspendisse potenti. Quisque ac nisi finibus, volutpat lacus eget, faucibus nisl. Quisque sed nunc risus. Etiam ultrices varius interdum. Mauris sed commodo orci. Nunc nulla turpis, lobortis sed tortor vitae, mollis fermentum eros. Ut laoreet facilisis purus non commodo. Vivamus mattis eros sodales rhoncus scelerisque. Fusce laoreet sapien sed nibh ornare blandit. Aliquam vulputate vulputate mauris id molestie. Pellentesque eget risus pulvinar, iaculis nisl aliquet, ornare nisi. Mauris porttitor ipsum a turpis fringilla, sit amet interdum nisl gravida. Nam cursus elementum tellus, nec rutrum dui malesuada id. Vestibulum interdum gravida eros, sed vestibulum diam convallis accumsan. Nullam porttitor nibh id est congue, sit amet mattis ex porta.', 'Development', '1/1/2018', 'TFS', 'HH', '12/25/2017', '1.1.8', '2/2/2018', '1/30/2018', '1.1.8.1'),
/* INSERT QUERY NO: 4 */
(6, 'Task', '4', 'Add Submenues to the website', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla ut orci scelerisque, viverra purus sed, ultrices mauris. Vestibulum imperdiet vitae libero eu ornare. Interdum et malesuada fames ac ante ipsum primis in faucibus. Maecenas tincidunt gravida est ut feugiat. Nulla magna magna, posuere non risus vel, aliquam lacinia felis. Phasellus eu augue id enim feugiat eleifend. Duis sit amet ligula imperdiet, euismod felis in, placerat risus. Duis ultrices magna eget ultrices viverra.', 'Development', '1/1/2018', 'TFS', 'HH', '11/22/2017', '1.1.8', '2/2/2018', '1/30/2018', '1.1.8.1'),
/* INSERT QUERY NO: 5 */
(7, 'Task', '4', 'add Main xxx Page Text', 'Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Suspendisse ultrices molestie est, eu tempus orci gravida ac. Ut augue felis, interdum at nulla congue, mattis eleifend orci. Donec lobortis, ex a ornare placerat, erat tellus iaculis justo, nec vestibulum sem tellus placerat ipsum. Morbi tincidunt quam ac aliquet ultrices. Sed interdum eros quis ligula sollicitudin gravida. Aliquam suscipit quam id iaculis varius. Phasellus dictum odio in pulvinar volutpat. Praesent et imperdiet nunc. Aliquam quis aliquam magna. Nunc sollicitudin, turpis eget mattis semper, justo nulla hendrerit felis, consectetur imperdiet ipsum massa ac lectus. Suspendisse nibh ipsum, tincidunt id augue mollis, lacinia vestibulum neque. In ullamcorper dui in nisl tempor pulvinar. Mauris non scelerisque tellus.', 'Development', '1/1/2018', 'TFS', 'HH', '11/23/2017', '1.1.8', '2/2/2018', '1/30/2018', '1.1.8.1'),
/* INSERT QUERY NO: 6 */
(8, 'Bug', '4', 'Fix Sitemap', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla ut orci scelerisque, viverra purus sed, ultrices mauris. Vestibulum imperdiet vitae libero eu ornare. Interdum et malesuada fames ac ante ipsum primis in faucibus. Maecenas tincidunt gravida est ut feugiat. Nulla magna magna, posuere non risus vel, aliquam lacinia felis. Phasellus eu augue id enim feugiat eleifend. Duis sit amet ligula imperdiet, euismod felis in, placerat risus. Duis ultrices magna eget ultrices viverra.', 'Support', '1/1/2018', 'SupportSystem', 'Client1', '12/2/2017', '1.1.8', '2/2/2018', '1/30/2018', '1.1.8.1'),
/* INSERT QUERY NO: 7 */
(16, 'Bug', '4', 'Web Site, Training Center: create a sub menu for the demo', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Support', '1/1/2018', 'SupportSystem', 'Client1', '12/3/2017', '1.1.8', '2/2/2018', '1/30/2018', '1.1.8.1'),
/* INSERT QUERY NO: 8 */
(17, 'Bug', '4', 'Web Site, Training Center: do an error catching', 'In vehicula magna dignissim arcu laoreet imperdiet. Aenean bibendum et quam vitae finibus. Proin eu augue elit. Vestibulum iaculis libero est, at vulputate augue ultricies eu. Morbi ultrices viverra rhoncus. Integer eget urna vel dui tincidunt iaculis euismod nec metus. Phasellus ornare lectus quis quam porta, nec iaculis eros aliquam. Cras sed magna mollis risus tristique vulputate quis non dui. Proin sed facilisis enim. Pellentesque facilisis, felis et elementum ultricies, ex eros dignissim ipsum, et gravida dolor urna at tortor. Fusce tincidunt pulvinar nisl in consectetur. Mauris ac vulputate magna. Sed finibus at nisl pretium mollis. In neque nisl, varius egestas enim vel, maximus rhoncus metus.', 'Development', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '2/2/2018', '1/30/2018', '1.1.8.1'),
/* INSERT QUERY NO: 9 */
(27, 'Feature', '', 'WebSite Graphics and Layout', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Development', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.2'),
/* INSERT QUERY NO: 10 */
(250, 'User Story', '27', 'Preparing Site for New xxxxxs Promotion', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Support', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.2'),
/* INSERT QUERY NO: 11 */
(251, 'Task', '250', 'Split the page', 'In vehicula magna dignissim arcu laoreet imperdiet. Aenean bibendum et quam vitae finibus. Proin eu augue elit. Vestibulum iaculis libero est, at vulputate augue ultricies eu. Morbi ultrices viverra rhoncus. Integer eget urna vel dui tincidunt iaculis euismod nec metus. Phasellus ornare lectus quis quam porta, nec iaculis eros aliquam. Cras sed magna mollis risus tristique vulputate quis non dui. Proin sed facilisis enim. Pellentesque facilisis, felis et elementum ultricies, ex eros dignissim ipsum, et gravida dolor urna at tortor. Fusce tincidunt pulvinar nisl in consectetur. Mauris ac vulputate magna. Sed finibus at nisl pretium mollis. In neque nisl, varius egestas enim vel, maximus rhoncus metus.', 'Support', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.2'),
/* INSERT QUERY NO: 12 */
(254, 'Task', '250', 'Change the Flier', 'In vehicula magna dignissim arcu laoreet imperdiet. Aenean bibendum et quam vitae finibus. Proin eu augue elit. Vestibulum iaculis libero est, at vulputate augue ultricies eu. Morbi ultrices viverra rhoncus. Integer eget urna vel dui tincidunt iaculis euismod nec metus. Phasellus ornare lectus quis quam porta, nec iaculis eros aliquam. Cras sed magna mollis risus tristique vulputate quis non dui. Proin sed facilisis enim. Pellentesque facilisis, felis et elementum ultricies, ex eros dignissim ipsum, et gravida dolor urna at tortor. Fusce tincidunt pulvinar nisl in consectetur. Mauris ac vulputate magna. Sed finibus at nisl pretium mollis. In neque nisl, varius egestas enim vel, maximus rhoncus metus.', 'Development', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.2'),
/* INSERT QUERY NO: 13 */
(255, 'Task', '250', 'Testing Quote request', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Development', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.2'),
/* INSERT QUERY NO: 14 */
(256, 'Task', '250', 'Testing Trial Request', 'request menu', 'Development', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.2'),
/* INSERT QUERY NO: 15 */
(259, 'User Story', '', 'Bugs from Prior Development', '', 'Development', '1/9/2018', 'SupportSystem', 'Client2', '12/11/2018', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 16 */
(260, 'Bug', '259', 'Selected Menu Item Does Not Change Color', '', 'Support', '1/9/2018', 'SupportSystem', 'Client2', '12/12/2018', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 17 */
(261, 'Bug', '259', 'Hints under the menu items', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Support', '1/9/2018', 'SupportSystem', 'Client2', '12/11/2018', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 18 */
(262, 'User Story', '30', 'Allow traffic tracking for the Wiki', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Development', '1/16/2018', 'SupportSystem', 'Client2', '12/13/2018', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 19 */
(263, 'Task', '', ' change colors ', 'In vehicula magna dignissim arcu laoreet imperdiet. Aenean bibendum et quam vitae finibus. Proin eu augue elit. Vestibulum iaculis libero est, at vulputate augue ultricies eu. Morbi ultrices viverra rhoncus. Integer eget urna vel dui tincidunt iaculis euismod nec metus. Phasellus ornare lectus quis quam porta, nec iaculis eros aliquam. Cras sed magna mollis risus tristique vulputate quis non dui. Proin sed facilisis enim. Pellentesque facilisis, felis et elementum ultricies, ex eros dignissim ipsum, et gravida dolor urna at tortor. Fusce tincidunt pulvinar nisl in consectetur. Mauris ac vulputate magna. Sed finibus at nisl pretium mollis. In neque nisl, varius egestas enim vel, maximus rhoncus metus.', 'Development', '1/16/2018', 'SupportSystem', 'Client2', '12/14/2018', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 20 */
(264, 'Bug', '30', 'Fix Sitemap', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Support', '1/16/2018', 'SupportSystem', 'Client1', '12.12.2018', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 21 */
(265, 'User Story', '250', 'SALES: develop a template', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Development', '1/16/2018', 'TFS', 'HH', '', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 22 */
(30, 'Feature', '', 'WebSite Analytics', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Development', '1/9/2018', 'TFS', 'HH', '', '1.1.8', '', '', '1.1.8.2'),
/* INSERT QUERY NO: 23 */
(266, 'User Story', '', 'Get a Credit Card provider quick books', 'In vehicula magna dignissim arcu laoreet imperdiet. Aenean bibendum et quam vitae finibus. Proin eu augue elit. Vestibulum iaculis libero est, at vulputate augue ultricies eu. Morbi ultrices viverra rhoncus. Integer eget urna vel dui tincidunt iaculis euismod nec metus. Phasellus ornare lectus quis quam porta, nec iaculis eros aliquam. Cras sed magna mollis risus tristique vulputate quis non dui. Proin sed facilisis enim. Pellentesque facilisis, felis et elementum ultricies, ex eros dignissim ipsum, et gravida dolor urna at tortor. Fusce tincidunt pulvinar nisl in consectetur. Mauris ac vulputate magna. Sed finibus at nisl pretium mollis. In neque nisl, varius egestas enim vel, maximus rhoncus metus.', 'Development', '1/16/2018', 'TFS', 'HH', '', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 24 */
(267, 'User Story', '30', 'Add Google Analytics Everywhere in the Wiki', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget elit lobortis, viverra lorem et, elementum nibh. Aenean scelerisque nulla sed quam aliquam, ut volutpat eros lacinia. Phasellus fringilla lectus lectus, in eleifend nulla condimentum et. Donec feugiat ornare libero, ac laoreet ipsum tincidunt sit amet. Curabitur blandit scelerisque malesuada. Praesent quis tortor orci. Nullam vitae elementum orci. Aenean sodales leo turpis, at rhoncus lacus facilisis ut. Praesent a magna vitae magna suscipit aliquet. Cras quis nisi vitae neque tempus consectetur. Curabitur dolor velit, facilisis faucibus arcu nec, elementum tempus arcu. Donec non dui finibus, luctus neque vel, vehicula nulla. Sed feugiat est ligula, id luctus nunc convallis sit amet.', 'Development', '1/16/2018', 'TFS', 'HH', '', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 25 */
(268, 'User Story', '30', 'Add the keywords everywhere in the wiki to move SEO up', 'Lorem', 'Development', '1/16/2018', 'TFS', 'HH', '', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 26 */
(269, 'User Story', '30', 'Add interlinking between wiki and the site', 'Lorem', 'Support', '1/16/2018', 'TFS', 'HH', '', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1'),
/* INSERT QUERY NO: 27 */
(270, 'User Story', '30', 'Add Bing Analytics plugin', 'Ipsum', 'Support', '1/16/2018', 'TFS', 'HH', '', '1.1.9', '2/22/2018', '2/15/2018', '1.1.9.1');


----------------ITERATE THROUGH spreadSheet
DECLARE @count INT;
SET @count = 1;
    
WHILE @count<= 27
BEGIN
---PRODUCT ID
   PRINT @count
   DECLARE @prodID INT EXECUTE @prodID = getProductID
-------------------------------------RELEASES-----------------------------------------
    DECLARE @releaseID INT;
    DECLARE @releaseName VARCHAR(10);
    SET @releaseName = (SELECT release_version FROM spreadSheet WHERE row_id = @count)
    BEGIN TRY
        INSERT INTO releases (product_id,release_version)
        SELECT @prodID,release_version FROM spreadSheet WHERE row_id = @count
    END TRY
    BEGIN CATCH
    END CATCH
    --- CHANGE TO ACTUALLY CALL THE ROWS OR ELSE IT WILL ALWAYS BE THE CURRENT ROW
    SET @releaseID = (SELECT release_id FROM releases WHERE release_version = @releaseName)
    
-----------------------------------------VERSIONS-----------------------------------------------
    DECLARE @versionID BIGINT;
    DECLARE @versionName VARCHAR(10);
    DECLARE @notifiedDate DATE;
    DECLARE @releasedDate DATE;
-----------NULL DATES----------
    SET @notifiedDate = (
    SELECT CASE notification_date WHEN '' THEN NULL
    ELSE notification_date END AS notification_date
    FROM spreadSheet WHERE row_id = @count)
    SET @releasedDate = (
    SELECT CASE release_date WHEN '' THEN NULL
    ELSE release_date END AS release_date
    FROM spreadSheet WHERE row_id = @count)
-------------------------------
    SET @versionName = (SELECT software_version FROM spreadSheet WHERE row_id = @count)
    BEGIN TRY
        INSERT INTO versions (release_id,version_name,notified_date,release_date)
        SELECT @releaseID, software_version,@notifiedDate,@releasedDate FROM spreadSheet WHERE row_id = @count
    END TRY
    BEGIN CATCH
    END CATCH
    SET @versionID = (SELECT version_id FROM versions WHERE version_name = @versionName)
-------------------------------------------HIERARCHY-------------------------------------------------
    DECLARE @hierarchyID INT;
    SET @hierarchyID = (SELECT pid FROM spreadSheet WHERE row_id = @count)
    DECLARE @recordedDate DATE;
    SET @recordedDate = (
    SELECT CASE recorded_date WHEN '' THEN NULL
    ELSE recorded_date END AS recorded_date
    FROM spreadSheet WHERE row_id = @count)
    BEGIN TRY
        INSERT INTO hierarchies (hierarchy_pid,type_name,hierarchy_ppid,object_title,object_description,activity,soa_name,reported_name,created_date,recorded_date,version_id)
        SELECT pid,type_char,ppid,title,description,activity,soa,reported_by, created_date, @recordedDate, @versionID FROM spreadSheet WHERE row_id = @count
    END TRY
    BEGIN CATCH
    END CATCH
   SET @count = @count + 1;
END;




IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[spreadSheet]') AND type in (N'U'))
DROP TABLE [dbo].[spreadSheet]
