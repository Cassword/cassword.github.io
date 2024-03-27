<?php session_start(); ?>
<header>
  <nav class="navbar navbar-expand-lg navbar-light ">
    <a class="navbar-brand" href="index.php">
      <img id="NavbarBrand" src="images/KNIGHT_DARK.png" width="30" height="30" alt="Everything Everything Navbar Icon">
    </a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarNav">
      <ul class="navbar-nav mx-auto">
        <li class="nav-item mx-2 <?php if ($_SERVER['PHP_SELF'] == '/index.php') echo 'active'; ?>">
          <a class="nav-link" href="index.php">Home <span class="sr-only">(current)</span></a>
        </li>
        <li class="nav-item mx-2 <?php if ($_SERVER['PHP_SELF'] == '/aboutMe.php') echo 'active'; ?>">
          <a class="nav-link" href="aboutMe.php">About </a>
        </li>
        <li class="nav-item mx-2 <?php if ($_SERVER['PHP_SELF'] == '/uniWork.php') echo 'active'; ?>">
          <a class="nav-link" href="uniWork.php">Coursework</a>
        </li>
        <li class="nav-item mx-2 <?php if ($_SERVER['PHP_SELF'] == '/misc.php') echo 'active'; ?>">
          <a class="nav-link" href="misc.php">Miscellaneous</a>
        </li>
      </ul>
    </div>
  </nav>
</header>