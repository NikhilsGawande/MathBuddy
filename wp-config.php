<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', 'wordpress');

/** MySQL database username */
define('DB_USER', 'wordpressuser');

/** MySQL database password */
define('DB_PASSWORD', 'password');

/** MySQL hostname */
define('DB_HOST', 'localhost');

/** Database Charset to use in creating database tables. */
define('DB_CHARSET', 'utf8');

/** The Database Collate type. Don't change this if in doubt. */
define('DB_COLLATE', '');

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         ',S|v~>81f{!Z=k7.bX%QcL)k>j6$i8WO<-HfII=>-fG|1k8Xe%j| =he:Cajd2-`');
define('SECURE_AUTH_KEY',  'Q|RhGGWZ#(hZ+;U/XbJ]SQR0vIVh.-|aZq+MCHN8.6lG<f6-E&E}C`1&nth!ydp/');
define('LOGGED_IN_KEY',    '3i;bgBcD`VPYs.B(2<%`^Za5.RzXk+at^%PbJC*UFvN!44veJqmum9&7Pr{+p;!*');
define('NONCE_KEY',        ':z3f13Lp}BXPO~OZ]7K3HNhb~[gqVyQK-${|G`,?+l{8;OH(@M2,(DF{Zr:D/;J}');
define('AUTH_SALT',        'wxcLMBrL-x!8_u)QGKT5411qw)`D<dylo_Y&?NKQk&bUvB|JI0-N&kh2*&4fo-2m');
define('SECURE_AUTH_SALT', 'YXHjBP88t(CwNcL?-_u4r|w+#c>e^Yh)EtvzHjy,F^ApWAJI6 >+7D^3.8IjeDzP');
define('LOGGED_IN_SALT',   '~?$@,,,609aH/gd+zocinV.XdFd@&Tu|a6VB2(L/gAPEt;pV+^+0[i?o6Qx6v7Q>');
define('NONCE_SALT',       'd-(ce7~ObS&INvD-5B-]?fPM-|(}(?K3X{nH2&nJf&v}PQ)[h0VJ?)g1|dgYH*Rc');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix  = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define('WP_DEBUG', false);

/* That's all, stop editing! Happy blogging. */

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');

/* Added this line to upload plugin locally */

define('FS_METHOD', 'direct');
